//
// Created by alan on 3/28/22.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <jni.h>

#include "gpioz.h"

#ifdef __cplusplus
extern "C"{
#endif

int gpio_export(char* gpio_num)
{
    FILE *fp;

    char *gpio_ept_pathname = "/sys/class/gpio/export";

    fp = fopen(gpio_ept_pathname, "w");

    if(fp == NULL)
    {
        printf("%s: can't open file /sys/class/gpio/export\n", __func__);
        return -1;
    }

    if(1 != fwrite(gpio_num, strlen(gpio_num), 1, fp))
    {
        printf("%s: can't write %s to %s\n", __func__, gpio_num, gpio_ept_pathname);
        fclose(fp);
        return -1;
    }

    fclose(fp);

    return 0;
}


int gpio_unexport(char* gpio_num)
{
    FILE *fp;

    char *gpio_uept_pathname = "/sys/class/gpio/unexport";

    fp = fopen(gpio_uept_pathname, "w");

    if(fp == NULL)
    {
        printf("%s: can't open file /sys/class/gpio/unexport\n", __func__);
        return -1;
    }

    if(1 != fwrite(gpio_num, strlen(gpio_num), 1, fp))
    {
        printf("%s: can't write %s to %s\n", __func__, gpio_num, gpio_uept_pathname);
        fclose(fp);
        return -1;
    }

    fclose(fp);

    return 0;
}

int gpio_set_direction(char *gpio_num, char *dir)
{
    FILE *fp;

    char fmt[128];

    if(strcmp(dir, "in") != 0 && strcmp(dir, "out") != 0)
    {
        printf("Only \"in\" or \"our\" can be chosen as directions.\n");
        return -1;
    }

    sprintf(fmt, "/sys/class/gpio/gpio%s/direction", gpio_num);

    fp = fopen(fmt, "w");

    if(fp == NULL)
    {
        printf("%s: can't open file /sys/class/gpio%s/direction\n", __func__, gpio_num);
        return -1;
    }

    if(1 != fwrite(dir, strlen(dir), 1, fp))
    {
        printf("%s: can't write %s to %s\n", __func__, dir, fmt);
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

int gpio_set_value(char *gpio_num, char *val)
{
    FILE *fp;

    char fmt[128];

    if(strcmp(val, "1") != 0 && strcmp(val, "0") != 0)
    {
        printf("Only \"1\" or \"0\" can be chosen as directions.\n");
        return -1;
    }

    sprintf(fmt, "/sys/class/gpio/gpio%s/value", gpio_num);

    fp = fopen(fmt, "w");

    if(fp == NULL)
    {
        printf("%s: can't open file /sys/class/gpio%s/value\n", __func__, gpio_num);
        return -1;
    }

    if(1 != fwrite(val, strlen(val), 1, fp))
    {
        printf("%s: can't write %s to %s\n", __func__, val, fmt);
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

int gpio_get_value(char *gpio_num, char *val)
{
    FILE *fp;

    char fmt[128];

    sprintf(fmt, "/sys/class/gpio/gpio%s/value", gpio_num);

    fp = fopen(fmt, "r");

    if (fp == NULL) {
        printf("%s: can't open file /sys/class/gpio%s/value\n", __func__, gpio_num);
        return -1;
    }

    if (1 != fread(val, 1, 1, fp)) {
        printf("%s: can't read from %s\n", __func__, fmt);
        fclose(fp);
        return -1;
    }
}

JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_export(JNIEnv *env, jobject thiz, jint gpio_num)
{

}


JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_unexport(JNIEnv *env, jobject thiz, jint gpio_num) {
    // TODO: implement unexport()
}

JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_setDirection(JNIEnv *env, jobject thiz, jint gpio_num, jint dirct) {
    // TODO: implement setDirection()
}

JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_setHigh(JNIEnv *env, jobject thiz, jint gpio_num) {
    // TODO: implement setHigh()
}

JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_setLow(JNIEnv *env, jobject thiz, jint gpio_num) {
    // TODO: implement setLow()
}

#ifdef __cplusplus
}
#endif




