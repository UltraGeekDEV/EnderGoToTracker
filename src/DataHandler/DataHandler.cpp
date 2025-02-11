#include "DataHandler.h"

bool DataHandler::CheckAndHandle(){
    if(doneReading){
        doneReading = false;
        free(buf);
        buf = nullptr;
        cur_byte = 0;
    }
    if(serial.available()){
        if(cur_byte == 0){
            command = (ActionType)serial.read();
            cur_byte++;
            serial.println("Command:");
            serial.println((byte)command);
        }
        else if(cur_byte == 1){
            buf_len = (uint8_t)serial.read();
            cur_byte++;
            serial.println("Buf len:");
            serial.println((byte)buf_len);
        }else if(cur_byte < buf_len + 2){
            if(cur_byte == 2){
                buf = (uint8_t*)malloc(buf_len);
            }
            buf[cur_byte-2] = (uint8_t)serial.read();
            cur_byte++;
        }
        if(cur_byte == buf_len+2){
            doneReading = true;
            serial.println("Done reading");
        }
    }
    
    return doneReading;
}