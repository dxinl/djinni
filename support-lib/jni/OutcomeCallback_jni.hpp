// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from artists_panel_info_callback.djinni

#pragma once

#include "djinni_support.hpp"
#include "OutcomeCallback.hpp"
#include "Outcome_jni.hpp"

namespace djinni {

template<class R, class E>
class NativeOutcomeCallback final
    : JniInterface<
        OutcomeCallback<typename R::CppType, typename E::CppType>, NativeOutcomeCallback<R, E>> {
private:
    using RCppType = typename R::CppType;
    using ECppType = typename E::CppType;
    using I = OutcomeCallback<RCppType, ECppType>;

public:
    using CppType = std::shared_ptr<I>;
    using CppOptType = std::shared_ptr<I>;
    using JniType = jobject;

    using Boxed = NativeOutcomeCallback<R, E>;

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

        void Callback(const expected<RCppType, ECppType> &c_r) override {
            auto jniEnv = jniGetThreadEnv();
            JniLocalScope jscope(jniEnv, 10);
            const auto &data = JniClass<Boxed>::get();
            jniEnv->CallVoidMethod(
                this->get().get(), data.method_callback,
                get(Outcome<R, E>::fromCpp(jniEnv, c_r)));
            jniExceptionCheck(jniEnv);
        }

    private:
        friend JniInterface<I, Boxed>;
    };

    const GlobalRef<jclass>
        clazz{jniFindClass("com/bytedance/djinni/OutcomeCallback")};
    const jmethodID
        method_callback
        {jniGetMethodID(clazz.get(), "callback", "(Lcom/snapchat/djinni/Outcome;)V")};
};

} // namespace djinni
