#include "multibuffer.h"

using namespace Buffer;

template <typename T>
MultiRingBuffer<T>::MultiRingBuffer() :
Base<T>()
{
}

template <typename T>
MultiRingBuffer<T>::MultiRingBuffer(
        int_fast32_t bufferSize,
        int_fast8_t ringSize,
        int_fast8_t numBuffers
    )
{
    set_size(bufferSize, ringSize, numBuffers);
}

template <typename T>
MultiRingBuffer<T>::MultiRingBuffer(const MultiRingBuffer& obj) :
_numBuffers(obj._numBuffers),
Base<T>(obj)
{
    int_fast8_t readidx = obj.globalReadIndex;
    this->globalReadIndex = readidx;
    int_fast8_t writeidx = obj.globalWriteIndex;
    this->globalWriteIndex = writeidx;
    int_fast8_t procidx = obj.globalProcessingIndex;
    this->globalProcessingIndex = procidx;
}

template <typename T>
MultiRingBuffer<T>::~MultiRingBuffer()
{
}

template <typename T>
bool MultiRingBuffer<T>::size_is_set() const
{
    for (std::shared_ptr<RingBuffer<T>> ptr: this->buffers)
    {
        if (ptr == nullptr || !ptr->size_is_set()) return false;
    }

    return (
            (this->buffers.size() > 0)
            && (this->_ringLength > 0)
            && (this->_bufferLength > 0)
        );
}

template <typename T>
void MultiRingBuffer<T>::set_size(
        int_fast32_t bufferSize,
        int_fast8_t ringSize,
        int_fast8_t numBuffers
    )
{
    #if _DEBUG
    if (numBuffers < 2) throw BUFFER_COUNT_TOO_SHORT;
    #endif

    Base<T>::set_size(bufferSize, ringSize);
    this->_numBuffers = numBuffers;
    this->buffers.reserve(numBuffers);
    for (int i(0); i < numBuffers; ++i)
    {
        std::shared_ptr<RingBuffer<T>> ptr = std::make_shared<RingBuffer<T>>(
                bufferSize,
                ringSize
            );
        this->buffers.push_back(ptr);
    }
}










template class Buffer::MultiRingBuffer<int8_t>;
template class Buffer::MultiRingBuffer<uint8_t>;
template class Buffer::MultiRingBuffer<int16_t>;
template class Buffer::MultiRingBuffer<uint16_t>;
template class Buffer::MultiRingBuffer<int32_t>;
template class Buffer::MultiRingBuffer<uint32_t>;
template class Buffer::MultiRingBuffer<int64_t>;
template class Buffer::MultiRingBuffer<uint64_t>;

#if (int32_t != int)
template class Buffer::MultiRingBuffer<int>;
#endif

#if (int32_t != int_fast32_t)
template class Buffer::MultiRingBuffer<int_fast8_t>;
template class Buffer::MultiRingBuffer<uint_fast8_t>;
template class Buffer::MultiRingBuffer<int_fast16_t>;
template class Buffer::MultiRingBuffer<uint_fast16_t>;
template class Buffer::MultiRingBuffer<int_fast32_t>;
template class Buffer::MultiRingBuffer<uint_fast32_t>;
template class Buffer::MultiRingBuffer<int_fast64_t>;
template class Buffer::MultiRingBuffer<uint_fast64_t>;
#endif

template class Buffer::MultiRingBuffer<float>;
template class Buffer::MultiRingBuffer<double>;
template class Buffer::MultiRingBuffer<long double>;

#if (int8_t != char)
template class Buffer::MultiRingBuffer<char>;
template class Buffer::MultiRingBuffer<unsigned char>;
#endif

template class Buffer::MultiRingBuffer<wchar_t>;
template class Buffer::MultiRingBuffer<char16_t>;
template class Buffer::MultiRingBuffer<char32_t>;

