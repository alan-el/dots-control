//
// Created by alan on 3/23/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <android/log.h>

#include <jni.h>
#include "include/uartz.h"

#ifdef __cplusplus
extern "C"{
#endif

#define UARTZ_LOG_TAG "uartz.c"
#define UARTZ_LOGI(...) __android_log_print(ANDROID_LOG_INFO,UARTZ_LOG_TAG,__VA_ARGS__)
#define UARTZ_LOGE(...) __android_log_print(ANDROID_LOG_ERROR, UARTZ_LOG_TAG, __VA_ARGS__)

JNIEXPORT jint JNICALL
Java_com_sightcare_dotscntl_SerialPort_open(JNIEnv *env, jobject thiz, jstring path)
{
    const char *pathname = (*env)->GetStringUTFChars(env, path, 0);

    if (!pathname)
    {
        pathname = "/dev/ttyS0";
    }

    jint ret = open(pathname, O_RDWR | O_NOCTTY);
    if(ret == -1)
        UARTZ_LOGE("open failed.\n");

    (*env)->ReleaseStringUTFChars(env, path, pathname);

    return ret;
}

JNIEXPORT void JNICALL
Java_com_sightcare_dotscntl_SerialPort_close(JNIEnv *env, jobject thiz, jint fd)
{
    int ret = close(fd);
    if (ret == -1)
        UARTZ_LOGE("close failed.\n");
}

JNIEXPORT jint JNICALL
Java_com_sightcare_dotscntl_SerialPort_set(JNIEnv *env, jobject thiz, jint fd, jint baudrate) {
    struct termios term;

    int ret;

    switch (baudrate)
    {
        case 9600:
            baudrate = B9600;
            break;
        case 19200:
            baudrate = B19200;
            break;
        case 38400:
            baudrate = B38400;
            break;
        case 57600:
            baudrate = B57600;
            break;
        case 115200:
            baudrate = B115200;
            break;
        default:
            return -1;
    }

    ret = tcgetattr(fd, &term);
    if (ret == -1)
        return ret;

    ret = cfsetispeed(&term, baudrate);
    if (ret == -1)
        return ret;

    ret = cfsetospeed(&term, baudrate);
    if (ret == -1)
        return ret;

    cfmakeraw(&term);

    term.c_cc[VTIME] = 0;
    term.c_cc[VMIN] = 1;

    ret = tcsetattr(fd, TCSANOW, &term);
    if (ret == -1)
        return ret;

    return 0;
}

JNIEXPORT jint JNICALL
Java_com_sightcare_dotscntl_SerialPort_send(JNIEnv *env, jobject thiz, jint fd, jbyteArray tb,
                                      jint count)
{
    jbyte *jtb = (*env)->GetByteArrayElements(env, tb, 0);

    int ret = write(fd, jtb, count);
    if(ret != count)
        UARTZ_LOGE("failed/partial send.\n");

    (*env)->ReleaseByteArrayElements(env, tb, jtb, 0);

    return ret;
}

JNIEXPORT jbyteArray JNICALL
Java_com_sightcare_dotscntl_SerialPort_receive(JNIEnv *env, jobject thiz, jint fd, jint count)
{
    jbyte rb[256];
    int ret = read(fd, rb, count);

    if (ret == -1)
    {
        UARTZ_LOGE("read.\n");
        jbyte ret_fail = -1;
        jbyteArray fail_ret = (*env)->NewByteArray(env, 1);
        (*env)->SetByteArrayRegion(env, fail_ret, 0, 0, &ret_fail);
        return fail_ret;
    }

    else if (ret != count)
        UARTZ_LOGE("partial receive.\n");

    jbyteArray jrb = (*env)->NewByteArray(env, ret);
    (*env)->SetByteArrayRegion(env, jrb, 0, ret - 1, rb);

    return jrb;
}

#ifdef __cplusplus
}
#endif