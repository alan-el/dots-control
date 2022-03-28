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

#define GPIO_MODE_TYPE_INPUT "in"
#define GPIO_MODE_TYPE_OUTPUT "out"


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

/* Reserve for future development. */
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
    FILE *fp;

    char *gpio_ept_pathname = "/sys/class/gpio/export";

    fp = fopen(gpio_ept_pathname, "w");

    if(fp == NULL)
    {
        /* TODO Using Andorid Log method instead. */
        printf("%s: can't open file /sys/class/gpio/export\n", __func__);
        return;
    }

    char num[8];
    memset(num, 0, sizeof(num));
    sprintf(num, "%d", gpio_num);

    if(1 != fwrite(num, strlen(num), 1, fp))
    {
        printf("%s: can't write %s to %s\n", __func__, num, gpio_ept_pathname);
        fclose(fp);
        return;
    }

    fclose(fp);
}


JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_unexport(JNIEnv *env, jobject thiz, jint gpio_num)
{
    FILE *fp;

    char *gpio_uept_pathname = "/sys/class/gpio/unexport";

    fp = fopen(gpio_uept_pathname, "w");

    if(fp == NULL)
    {
        printf("%s: can't open file /sys/class/gpio/unexport\n", __func__);
        return;
    }

    char num[8];
    memset(num, 0, sizeof(num));
    sprintf(num, "%d", gpio_num);

    if(1 != fwrite(num, strlen(num), 1, fp))
    {
        printf("%s: can't write %s to %s\n", __func__, num, gpio_uept_pathname);
        fclose(fp);
        return;
    }

    fclose(fp);
}

JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_setDirection(JNIEnv *env, jobject thiz, jint gpio_num, jint dirct)
{
    FILE *fp;

    char gpio_sd_pathname[128];
    memset(gpio_sd_pathname, 0, sizeof(gpio_sd_pathname));
    sprintf(gpio_sd_pathname, "/sys/class/gpio/gpio%d/direction", gpio_num);

    fp = fopen(gpio_sd_pathname, "w");

    if(fp == NULL)
    {
        printf("%s: can't open file %s\n", __func__, gpio_sd_pathname);
        return;
    }

    char dir[8];
    memset(dir, 0, sizeof(dir));
    if(0 == dirct)
    {
        sprintf(dir, GPIO_MODE_TYPE_INPUT);
    }
    else if(1 == dirct)
    {
        sprintf(dir, GPIO_MODE_TYPE_OUTPUT);
    }
    else
    {
        /* TODO error dirct value */
    }

    if(1 != fwrite(dir, strlen(dir), 1, fp))
    {
        printf("%s: can't write %s to %s\n", __func__, dir, gpio_sd_pathname);
        fclose(fp);
        return;
    }

    fclose(fp);
}

JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_setHigh(JNIEnv *env, jobject thiz, jint gpio_num)
{
    char num[8];
    memset(num, 0, sizeof(num));
    sprintf(num,"%d", gpio_num);

    gpio_set_value(num, "1");
}

JNIEXPORT void JNICALL
Java_com_zqn_dotscntl_GPIO_setLow(JNIEnv *env, jobject thiz, jint gpio_num)
{
    char num[8];
    memset(num, 0, sizeof(num));
    sprintf(num,"%d", gpio_num);

    gpio_set_value(num, "0");
}

#ifdef __cplusplus
}
#endif




