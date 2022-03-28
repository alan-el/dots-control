//
// Created by alan on 3/23/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>

#include <jni.h>
#include "uartz.h"

#ifdef __cplusplus
extern "C"{
#endif

JNIEXPORT jstring JNICALL
Java_com_zqn_dotscntl_SerialPort_NativeFoo(JNIEnv *env, jobject thiz, jint num) {
    char ret[256];
    sprintf(ret, "%d From UARTZ.\n", num);
    jstring back = (*env)->NewStringUTF(env, ret);
    return back;
}

JNIEXPORT jint JNICALL
Java_com_zqn_dotscntl_SerialPort_open(JNIEnv *env, jobject thiz, jstring path) {
    const char *pathname = (*env)->GetStringUTFChars(env, path, 0);

    if (!pathname) {
        pathname = "/dev/ttyS0";
    }

    jint ret = open(pathname, O_RDWR | O_NOCTTY);

    (*env)->ReleaseStringUTFChars(env, path, ret);

    return ret;
}

JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_SerialPort_close(JNIEnv *env, jobject thiz, jint fd) {
    int ret = close(fd);
    if (ret != 0)
        // TODO Using Andorid Log instead.
        perror("uart_close:");
}

JNIEXPORT jint JNICALL
Java_com_zqn_dotscntl_SerialPort_set(JNIEnv *env, jobject thiz, jint fd, jint baudrate) {
    struct termios term;

    int ret;

    switch (baudrate) {
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
    if (ret < 0)
        return ret;

    ret = cfsetispeed(&term, baudrate);
    if (ret < 0)
        return ret;

    ret = cfsetospeed(&term, baudrate);
    if (ret < 0)
        return ret;

    cfmakeraw(&term);

    term.c_cc[VTIME] = 0;
    term.c_cc[VMIN] = 1;

    ret = tcsetattr(fd, TCSANOW, &term);
    if (ret < 0)
        return ret;

    return 0;
}

JNIEXPORT jint JNICALL
Java_com_zqn_dotscntl_SerialPort_send(JNIEnv *env, jobject thiz, jint fd, jbyteArray tb,
                                      jint count) {
    jbyte *jtb = (*env)->GetByteArrayElements(env, tb, 0);

    int ret = write(fd, jtb, count);

    (*env)->ReleaseByteArrayElements(env, tb, jtb, 0);

    if (ret < 0) {
        perror("uart_send:");
        return -1;
    }

    return ret;
}

JNIEXPORT jbyteArray JNICALL
Java_com_zqn_dotscntl_SerialPort_receive(JNIEnv *env, jobject thiz, jint fd, jint count) {
    jbyte rb[256];
    int ret = read(fd, rb, count);

    if (ret < 0) {
        perror("uart_receive:");
        return -1;
    }

    jbyteArray jrb = (*env)->NewByteArray(env, ret);
    (*env)->SetByteArrayRegion(env, jrb, 0, ret - 1, rb);

    return jrb;
}

#ifdef __cplusplus
}
#endif