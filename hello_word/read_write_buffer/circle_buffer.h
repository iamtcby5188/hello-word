#pragma once
const int buf_status_free = 0;
const int buf_status_new_write = 1;

class circle_buffer
{
    struct buffer_head
    {
        long long p_read_point;
        long long p_write_point;
        int       used_size;
    };

    struct data_head
    {
        int buf_size;
        int buf_status;

        data_head(int size, int status)
        {
            buf_size = size;
            buf_status = status;
        }

    private:
        data_head(){}
    };
public:
    
    circle_buffer(int total_size, long long begin_pos);
    ~circle_buffer();

    void* read_buffer(int& buffer_size);
    bool write_buffer(int buffer_size, long long pos);
private:
    void* get_write_pos(int buffer_size) const;
    int m_total_size;
    
    long long  m_begin_pos;
    long long  m_end_pos;
    long long  m_begin_data_pos;
    buffer_head* m_head_pos;

private:
    circle_buffer(){};
};

