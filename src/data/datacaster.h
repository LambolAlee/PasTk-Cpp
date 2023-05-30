
#ifndef DATACASTER_H
#define DATACASTER_H


class DataCaster
{
public:
    void next() { m_index++; }
    int current() const { return m_index; };
    void setCurrent(int index) { m_index = index; }
    void resetCaster() { m_index = 0; }

private:
    int m_index;
};

#endif // DATACASTER_H
