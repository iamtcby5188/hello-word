#include "stdafx.h"
#include "circle_buffer.h"


circle_buffer::circle_buffer(int total_size, long long begin_pos)
    : m_begin_pos(begin_pos)
{
    if (total_size > sizeof(buffer_head))
    {
        m_total_size = total_size - sizeof(buffer_head);
    }
    m_begin_data_pos = m_begin_pos + sizeof(buffer_head);
    m_end_pos = m_begin_pos + total_size;
    m_head_pos = (buffer_head*)m_begin_pos;
}


circle_buffer::~circle_buffer()
{
}

void* circle_buffer::read_buffer(int& buffer_size)
{
    void* p_ret = nullptr;
    if (m_head_pos )
    {
        long long p_read = m_head_pos->p_read_point;
        if (m_head_pos->p_read_point == NULL)
        {
            p_read = m_begin_data_pos;
        }

        data_head dh(0,0);
        memcpy(&dh, (void*)p_read, sizeof(data_head));
        if (dh.buf_status == buf_status_new_write && dh.buf_size > 0)
        {
            buffer_size = dh.buf_size;
            p_ret = (void*)(p_read + sizeof(data_head));
            dh.buf_status = buf_status_free;
            memcpy((void*)p_read, &dh, sizeof(data_head));
            m_head_pos->p_read_point = p_read + buffer_size + sizeof(data_head);
            m_head_pos->used_size -= (dh.buf_size + sizeof(data_head));
        }
    }

    return p_ret;
}

bool circle_buffer::write_buffer(int buffer_size, long long pos)
{
    bool bRet(false);
    int dataSize = buffer_size + sizeof(data_head);
    void* p_write = get_write_pos(dataSize);
    if (p_write != NULL)
    {
        data_head dh(buffer_size,buf_status_new_write);
        memcpy(p_write, &dh, sizeof(data_head));
        p_write = (void*)((long long)p_write + sizeof(data_head));
        memcpy(p_write, (void*)pos,buffer_size);
        m_head_pos->used_size += dataSize;
        m_head_pos->p_write_point = (long long)p_write + buffer_size;
        bRet = true;
    }
    return bRet;
}


void* circle_buffer::get_write_pos(int buffer_size) const
{
    void* p_ret(NULL);
    if (m_head_pos && m_head_pos->used_size + buffer_size <= m_total_size)
    {
        if (m_head_pos->p_read_point == NULL && m_head_pos->p_write_point == NULL)
        {
            if (m_total_size >= buffer_size){
                p_ret = (void*)m_begin_data_pos;
            }
        }
        else if (m_head_pos->p_read_point != NULL && m_head_pos->p_write_point == NULL)
        {
            if (m_begin_data_pos + buffer_size < m_head_pos->p_read_point)
            {
                p_ret = (void*)m_begin_data_pos;
            }
        }
        else if (m_head_pos->p_read_point == NULL && m_head_pos->p_write_point != NULL)
        {
            if (m_head_pos->p_write_point + buffer_size <= m_end_pos)
            {
                p_ret = (void*)m_head_pos->p_write_point;
            }
        }
        else if (m_head_pos->p_read_point != NULL && m_head_pos->p_write_point != NULL)
        {
            if (m_head_pos->p_read_point > m_head_pos->p_write_point)
            {
                if (m_head_pos->p_write_point + buffer_size < m_head_pos->p_read_point)
                {
                    p_ret = (void*)m_head_pos->p_write_point;
                }
            }
            else
            {
                if (m_head_pos->p_write_point + buffer_size <= m_end_pos)
                {
                    p_ret = (void*)m_head_pos->p_write_point;
                }
                else if (m_begin_data_pos + buffer_size <= m_head_pos->p_read_point)
                {
                    p_ret = (void*)m_begin_data_pos;
                }
            }
        }
    }
    return p_ret;
}
