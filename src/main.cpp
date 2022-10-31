#include "multibuffer.h"

#define DATATYPE                    int8_t

int main(int argc, char** argv)
{
    try
    {
        #ifdef _DEBUG
        std::cout << "Debug mode enabled\n";
        #endif

        Buffer::MultiRingBuffer<DATATYPE, int_fast8_t> buff(4, 2, 2);

        std::vector<DATATYPE> vec;
        for (int i(0); i < buff.buffer_length(); ++i)
        {
            vec.emplace_back(i);
        }

        for (int i(0); i < buff.ring_length(); ++i)
        {
            buff.write(vec, false);
            std::cout << "samples buffered after write: " << buff.buffered() << '\n';
        }

        for (int j(0); j < buff.ring_length() - 1; ++j)
        {
            std::vector<DATATYPE> v = buff.buffers.at(0).read();
            for (int i(0); i < buff.buffer_length(); ++i)
            {
                std::cout << "index: " << +i << " value:\t\t" << +v.at(i) << '\n';
                std::cout << "\tshould be\t" << +vec.at(i) << '\n';
            }
        }
    }
    catch (Buffer::ringbuffer_err exc)
    {
        std::cerr << "Caught exception: " << exc << '\n';
        return exc;
    }

    return 0;
}
