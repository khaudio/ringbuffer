#include "multibuffer.h"

#define DATATYPE                    int8_t
#define MULTIRINGBUFF               false


int main(int argc, char** argv)
{
    try
    {
        #ifdef _DEBUG
        std::cout << "Debug mode enabled\n";
        #endif

        #if MULTIRINGBUFF
        Buffer::AtomicMultiRingBuffer<DATATYPE> buff(4, 2, 2);
        #else
        Buffer::AtomicMultiReadRingBuffer<DATATYPE> buff(4, 2);
        buff.set_num_readers(3);
        std::cout << "Num readers set to " << +buff.num_readers() << '\n';
        #endif

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
            #if MULTIRINGBUFF
            std::vector<DATATYPE> v = buff.buffers.at(0).read();
            #else
            std::vector<DATATYPE> v(buff.buffer_length());
            std::cout << "reading...\n";
            // v = buff.read();
            buff.read_samples(&(v[0]), buff.buffer_length());
            buff.read_samples(&(v[0]), buff.buffer_length());
            buff.read_samples(&(v[0]), buff.buffer_length());
            // buff.read_samples(&(v[0]), buff.buffer_length());
            std::cout << "samples read\n";
            #endif
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
