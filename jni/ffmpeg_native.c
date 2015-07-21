#include <math.h>
#include <ffmpeg/libavutil/opt.h>
#include <ffmpeg/libavcodec/avcodec.h>
#include <ffmpeg/libavutil/channel_layout.h>
#include <ffmpeg/libavutil/common.h>
#include <ffmpeg/libavutil/imgutils.h>
#include <ffmpeg/libavutil/mathematics.h>
#include <ffmpeg/libavutil/samplefmt.h>

#include "ffmpeg_native.h"

#ifdef __cplusplus
extern "C" {
#endif

// 获取数组的大小
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
// 指定要注册的类，对应完整的java类名
#define JNIREG_CLASS "com/example/myffmpeg4android/utils/FFmpegNative"

JNIEXPORT jint JNICALL native_avcodec_find_decoder
(JNIEnv *env, jobject obj, jint codecID)
{
	AVCodec *codec = NULL;

	/* register all formats and codecs */
	av_register_all();

	codec = avcodec_find_decoder(codecID);

	if (codec != NULL)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/*
 * Class:     com_example_myffmpeg4android_utils_FFmpegNative
 * Method:    avcodec_version
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL native_avcodec_version
(JNIEnv *env, jobject obj){
	char str[25];
	sprintf(str, "%d", avcodec_version());
	return (*env)->NewStringUTF(env, str);
}


// Java和JNI函数的绑定表
static JNINativeMethod method_table[] = {
    { "avcodec_find_decoder", "(I)I", (void *)native_avcodec_find_decoder },//绑定
    { "avcodec_version", "()Ljava/lang/String;", (void *)native_avcodec_version },
};

// 注册native方法到java中
static int registerNativeMethods(JNIEnv* env, const char* className,
        JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

int register_ndk_load(JNIEnv *env)
{
    // 调用注册方法
    return registerNativeMethods(env, JNIREG_CLASS,
            method_table, NELEM(method_table));
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    register_ndk_load(env);

    // 返回jni的版本
    return JNI_VERSION_1_4;
}



#ifdef __cplusplus
}
#endif
