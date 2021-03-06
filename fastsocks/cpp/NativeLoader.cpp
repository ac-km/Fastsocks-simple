//
// Created by 朱乾 on 17/3/23.
//

#include <jni.h>
#include <stdio.h>
#include "breakpad/client/linux/handler/exception_handler.h"
#include "breakpad/client/linux/handler/minidump_descriptor.h"

static google_breakpad::ExceptionHandler *exceptionHandler;

bool callback(const google_breakpad::MinidumpDescriptor &descriptor, void *context, bool succeeded) {
    printf("dump path: %s\n", descriptor.path());
    return succeeded;
}

extern "C" {
void Java_com_me_fastsocks_base_NativeLoader_init(JNIEnv* env, jobject obj, jstring filepath, bool enable) {
        if (enable) {
            const char *path = env->GetStringUTFChars(filepath, 0);
            google_breakpad::MinidumpDescriptor descriptor(path);
            exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, callback, NULL, true, -1);
        }
    }
}