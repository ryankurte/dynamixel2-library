
#pragma once

#include "SerialInterface.hpp"

#define MAX_BUFF_SIZE       128;

class MockDriver : Dynamixel::SerialDriver {
public:

    int Available()
    {
        return (_buff_in_head - _buff_in_tail) % MAX_BUFF_SIZE;
    }

    void Put(char c)
    {
        _buff_out[_buff_out_head % MAX_BUFF_SIZE] = c;
        _buff_out_head ++;
    }

    char Get()
    {
        char c = 0;

        if(_buff_in_tail != _buff_in_head) {
            c = _buff_in[_buff_in_tail % MAX_BUFF_SIZE];
            _buff_in_tail ++;
        }

        return c;
    }

    int FetchAvailable()
    {
        return (_buff_out_head - _buff_out_tail) % MAX_BUFF_SIZE;
    }

    void LoadGet(char c)
    {
        _buff_in[_buff_in_head % MAX_BUFF_SIZE] = c;
        _buff_in_head ++;
    }

    char FetchPut()
    {
        char c = 0;

        if(_buff_out_tail != _buff_out_head) {
            c = _buff_out[_buff_out_tail % MAX_BUFF_SIZE];
            _buff_out_tail ++;
        }

        return c;
    }

private:

    uint8_t _buff_out[MAX_BUFF_SIZE];
    int _buff_out_head = 0;
    int _buff_out_tail = 0;

    uint8_t _buff_in[MAX_BUFF_SIZE];
    int _buff_in_head = 0;
    int _buff_in_tail = 0;

};

