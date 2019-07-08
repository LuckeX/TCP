//
// Created by xyk on 19-6-19.
//

#ifndef PIPELINE_WRAPPER_H
#define PIPELINE_WRAPPER_H



#ifdef __cplusplus
extern "C" {
#endif

void call_listento(int port);
void call_connect(char* ip,int port);

void *call_getBuffer();

#ifdef __cplusplus
}
#endif



#endif //PIPELINE_WRAPPER_H
