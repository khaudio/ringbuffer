#ifndef MULTIBUFFER_H
#define MULTIBUFFER_H

#include "ringbuffer.h"

namespace Buffer
{

enum multiringbuffer_err
{
    BUFFER_COUNT_TOO_SHORT = -90,
};

template <typename T>
class MultiRingBuffer : public Base<T>
{

protected:

    int_fast8_t _numBuffers;

public:

    /* Global indices */
    std::atomic_int_fast8_t
        globalReadIndex{0},
        globalWriteIndex{0},
        globalProcessingIndex{0};

    std::vector<std::shared_ptr<RingBuffer<T>>> buffers;

public:

    MultiRingBuffer();
    MultiRingBuffer(
            int_fast32_t bufferSize,
            int_fast8_t ringSize,
            int_fast8_t numBuffers
        );
    MultiRingBuffer(const MultiRingBuffer& obj);

    ~MultiRingBuffer();

    bool size_is_set() const override;
    
    virtual void set_size(
            int_fast32_t bufferSize,
            int_fast8_t ringSize,
            int_fast8_t numBuffers
        );
    
    int_fast32_t size() const override;
    int_fast32_t total_size() const override;
    int_fast32_t num_buffers() const;

    void fill(T value = 0);
    void reset() override;

    std::shared_ptr<RingBuffer<T>> get_buffer(int_fast8_t bufferIndex);

// /*                          Sample Counters                         */

// public:

//     virtual int_fast32_t buffered() const;
//     virtual int_fast32_t bytes_buffered() const;

//     virtual int_fast32_t available() const;
//     virtual int_fast32_t bytes_available() const;

//     virtual int_fast32_t processed() const;
//     virtual int_fast32_t bytes_processed() const;

//     virtual int_fast32_t unprocessed() const;
//     virtual int_fast32_t bytes_unprocessed() const;

//     virtual int_fast32_t unread() const;
//     virtual int_fast32_t bytes_unread() const;

//     virtual int_fast32_t unwritten() const;
//     virtual int_fast32_t bytes_unwritten() const;

// /*                          Buffer Counters                         */

// public:

//     virtual int_fast32_t buffers_buffered() const;
//     virtual int_fast32_t buffers_available() const;
//     virtual int_fast32_t buffers_processed() const;

// /*                               Read                               */

// protected:

//     virtual std::vector<T> _read(int_fast8_t bufferIndex);

// public:

//     virtual std::vector<T> read(int_fast8_t bufferIndex);
//     virtual void read_samples(T* data, int_fast32_t length, int_fast8_t bufferIndex);
//     virtual void read_bytes(uint8_t* data, int_fast32_t numBytes, int_fast8_t bufferIndex);
//     virtual std::vector<T>* get_read_buffer(int_fast8_t bufferIndex);
//     virtual T* get_read_buffer_sample(int_fast8_t bufferIndex);
//     virtual uint8_t* get_read_buffer_byte(int_fast8_t bufferIndex);
//     virtual T* get_read_sample(int_fast8_t bufferIndex);
//     virtual uint8_t* get_read_byte(int_fast8_t bufferIndex);
//     virtual void rotate_read_index(int_fast8_t bufferIndex);
//     virtual void rotate_read_buffer(int_fast8_t bufferIndex);
//     virtual void rotate_partial_read(int_fast32_t length, int_fast8_t bufferIndex);
//     virtual void report_read_samples(int_fast32_t length, int_fast8_t bufferIndex);
//     virtual void report_read_bytes(int_fast32_t numBytes, int_fast8_t bufferIndex);

// /*                               Write                              */

// public:

//     virtual int_fast32_t write(T data, bool force = false);
//     virtual int_fast32_t write(std::vector<T> data, bool force = false);
//     virtual int_fast32_t write_samples(
//             T* data,
//             int_fast32_t length,
//             bool force = false
//         );
//     virtual int_fast32_t write_bytes(
//             uint8_t* data,
//             int_fast32_t numBytes,
//             bool force = false
//         );

//     virtual void rotate_write_index();
//     virtual void rotate_write_buffer(bool force = false);
//     virtual void rotate_partial_write(int_fast32_t length, bool force = false);
//     virtual void report_written_sample(int_fast32_t length);
//     virtual void report_written_byte(int_fast32_t numBytes);

};

};

#endif
