/**
  * Copyright 2023 Bytedance, Inc.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *    http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

#pragma once

#include "djinni_support.hpp"
#include "OutcomeCallback.hpp"
#include "Outcome_jni.hpp"

namespace djinni {

struct OutcomeCallbackJniInfo {
    const GlobalRef<jclass> clazz{jniFindClass("com/bytedance/djinni/OutcomeCallback")};
    const jmethodID method_callback{
        jniGetMethodID(clazz.get(), "callback", "(Lcom/snapchat/djinni/Outcome;Ljava/lang/Object;)V")
    };
};

template<typename RESULT, typename ERROR, typename OTHERS>
class NativeOutcomeCallback final
    : JniInterface<OutcomeCallback<typename RESULT::CppType, typename ERROR::CppType, typename OTHERS::CppType>, NativeOutcomeCallback<RESULT, ERROR, OTHERS>> {
    using ResultCppType = typename RESULT::CppType;
    using ErrorCppType = typename ERROR::CppType;
    using OthersCppType = typename OTHERS::CppType;
    using I = OutcomeCallback<ResultCppType, ErrorCppType, OthersCppType>;

public:
    using CppType = std::shared_ptr<I>;
    using CppOptType = std::shared_ptr<I>;
    using JniType = jobject;

    using Boxed = NativeOutcomeCallback<RESULT, ERROR, OTHERS>;

    ~NativeOutcomeCallback() = default;

    static CppType toCpp(JNIEnv *jniEnv, JniType j) {
        return JniClass<Boxed>::get()._fromJava(jniEnv, j);
    }
    static LocalRef<JniType> fromCppOpt(JNIEnv *jniEnv, const CppOptType &c) {
        return {jniEnv, JniClass<Boxed>::get()._toJava(jniEnv, c)};
    }
    static LocalRef<JniType> fromCpp(JNIEnv *jniEnv, const CppType &c) {
        return fromCppOpt(jniEnv, c);
    }

private:
    NativeOutcomeCallback() : JniInterface<I, Boxed>() {}
    friend JniClass<Boxed>;
    friend JniInterface<I, Boxed>;

    class JavaProxy final : JavaProxyHandle<JavaProxy>, public I {
    public:
        JavaProxy(JniType j) : JavaProxyHandle<JavaProxy>(jniGetThreadEnv(), j) {}
        ~JavaProxy() = default;

        void Callback(
            const expected<ResultCppType, ErrorCppType> &c_r,
            const OthersCppType &c_others
        ) override {
            auto jniEnv = jniGetThreadEnv();
            JniLocalScope jscope(jniEnv, 10);
            const auto &jniInfo = JniClass<OutcomeCallbackJniInfo>::get();
            jniEnv->CallVoidMethod(
                this->get().get(), jniInfo.method_callback,
                get(Outcome<RESULT, ERROR>::fromCpp(jniEnv, c_r)),
                get(OTHERS::fromCpp(jniEnv, c_others))
            );
            jniExceptionCheck(jniEnv);
        }

    private:
        friend JniInterface<I, Boxed>;
    };

};

} // namespace djinni
