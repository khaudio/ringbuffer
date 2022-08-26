#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <map>
#include <stdexcept>


namespace Buffer
{

enum ringbuffer_err
{
    RING_SIZE_TOO_SHORT = 140,
    BUFFER_NOT_INITIALIZED = 150,
};

template <typename T>
constexpr T get_zero()
{
    constexpr uint64_t exponent = (sizeof(T) * 8) - 1;
    uint64_t value = 2;
    for (int_fast32_t i(0); i < exponent; ++i) value *= 2;
    return (
            std::numeric_limits<T>::is_integer
            && std::is_unsigned<T>()
        ) ? (value - 1) : 0;
}

class Ring
{
public:
    uint_fast8_t ringLength;

    Ring();
    ~Ring();
};

template <typename T>
class RingBuffer : virtual public Ring
{
public:
    const static T _zero;

protected:
    uint_fast32_t
        _totalWritableLength,
        _buffered,
        _samplesWritten,
        _samplesRemaining,
        _samplesProcessed;

    bool _size_is_set();

public:
    uint_fast32_t
        bufferLength,
        totalRingSampleLength,
        bytesPerSample,
        bytesPerBuffer;
    uint_fast8_t
        readIndex,
        writeIndex,
        processingIndex;
    std::vector<std::vector<T>> ring;
    std::map<uint_fast8_t, bool> bufferProcessedState;

    RingBuffer();
    RingBuffer(uint_fast32_t bufferSize, uint_fast8_t ringSize);
    ~RingBuffer();

    virtual void set_size(uint_fast32_t bufferSize, uint_fast8_t ringSize);
    virtual size_t size();

    virtual void zero_fill();
    virtual void reset(bool zeroFill = false);

    virtual uint_fast32_t buffered();
    virtual uint_fast32_t available();
    virtual uint_fast32_t processed();
    virtual uint_fast32_t buffers_buffered();
    virtual uint_fast32_t buffers_available();
    virtual uint_fast32_t buffers_processed();
    virtual bool is_writable();

    virtual void rotate_read_index();
    virtual void rotate_write_index();
    virtual void rotate_processing_index();

    virtual void rotate_read_buffer(bool force = false);
    virtual void rotate_write_buffer(bool force = false);
    virtual void rotate_processing_buffer();

    virtual void rotate_partial_read(uint_fast32_t length, bool force = false);
    virtual void rotate_partial_write(uint_fast32_t length, bool force = false);
    virtual void rotate_partial_processing(uint_fast32_t length);

    virtual uint_fast8_t get_ring_index(std::vector<T>* bufferPtr);
    virtual uint_fast8_t get_ring_index(uint_fast8_t* bufferPtr);

    virtual std::vector<T>* get_read_buffer();
    virtual std::vector<T>* get_write_buffer();
    virtual std::vector<T>* get_processing_buffer();

    virtual uint_fast8_t* get_read_byte();
    virtual uint_fast8_t* get_write_byte();
    virtual uint_fast8_t* get_processing_byte();

/*                               Read                               */

protected:
    virtual const std::vector<T> _read() const;

public:
    virtual const std::vector<T> read(bool force = false);
    virtual void read_bytes(uint_fast8_t* data, size_t numBytes, bool force = false);
    virtual void read_samples(T* data, size_t length, bool force = false);

    /* Initial read once the buffer is initialized */
    virtual const std::vector<T> read_initial(bool force = false);
    virtual void read_bytes_initial(uint_fast8_t* data, size_t numBytes, bool force = false);
    virtual void read_samples_initial(T* data, size_t length, bool force = false);

/*                               Write                              */

public:
    virtual uint_fast32_t write(T data, bool force = false);
    virtual uint_fast32_t write(std::vector<T> data, bool force = false);
    virtual size_t write_bytes(uint_fast8_t* data, size_t numBytes, bool force = false);
    virtual size_t write_samples(T* data, size_t length, bool force = false);
    
    /* Initial write after data has been read to the buffer */
    virtual uint_fast32_t write_initial(T data, bool force = false);
    virtual uint_fast32_t write_initial(std::vector<T> data, bool force = false);
    virtual size_t write_bytes_initial(uint_fast8_t* data, size_t numBytes, bool force = false);
    virtual size_t write_samples_initial(T* data, size_t length, bool force = false);

/*                             Transform                            */

protected:
    virtual void _set_buffer_processed(uint_fast8_t ringIndex, bool state);
    virtual bool _is_buffer_processed(uint_fast8_t ringIndex);

public:
    virtual void set_buffer_processed(std::vector<T>* bufferPtr, bool state);
    virtual void set_buffer_processed(uint_fast8_t* bufferPtr, bool state);

    virtual bool is_buffer_processed(std::vector<T>* bufferPtr);
    virtual bool is_buffer_processed(uint_fast8_t* bufferPtr);
};

};

#endif
