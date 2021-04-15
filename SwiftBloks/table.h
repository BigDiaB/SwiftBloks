//
//  table.h
//  Alpha-Engine
//
//  Created by Benjamin Emde on 11.04.21.
//

#pragma once
#include <iostream>
template <class T>
struct table
{
private:
    bool can_change = true;
    int step = 8;
    bool has_limit = true;
    int size;
    int fill = 0;
    T* content;
    
public:
    table(int num, bool change)
    {
        can_change = change;
        size = num;
        T* temp[size];
        content = temp;
        for (int i = 0; i <= size; i++)
        {
            content[i] = NULL;
        }
    }
    
    table(int num)
    {
        size = num;
        T* temp = new T[size];
        content = temp;
        delete[] temp;
        for (int i = 0; i <= size; i++)
        {
            content[i] = NULL;
        }
    }
    
    table()
    {
        size = 0;
        T* temp = new T[size];
        content = temp;
        delete[] temp;
        for (int i = 0; i <= size; i++)
        {
            content[i] = NULL;
        }
        has_limit = false;
    }
    
    ~table(){}
    
    void set(T thing, int index)
    {
        if (index <= size)
        {
            content[index] = thing;
            fill++;
        }
    }
    void add(T thing)
    {
        {
        content[fill] = thing;
        fill++;
        }
        if (fill >= size + 1)
            resize();
    }
    
    void move(int now, int later)
    {
        T curr = at(now);
        T place = at(later);
        set(curr,later);
        set(place,now);
    }
    
    void delObj(T thing)
    {
        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (content[i] == thing)
            {
                content[i] = NULL;
                found = true;
            }
        }
        if (not found)
            std::cout << "couldn`t find that" << std::endl;
    }
    
    void delIndex(int index)
    {
        content[index] = NULL;
    }
    
    T at(int index)
    {
        return content[index];
    }
    
    int getSize()
    {
        return size;
    }
    
    int getFill()
    {
        return fill;
    }
    int getIndexByObj(T thing)
    {
        for (int i = 0; i < size; i++)
        {
            if (content[i] == thing)
                return i;
        }
        std::cout << "couldn't find that" << std::endl;
        return NULL;
    }
    
    void resize()
    {
        if (can_change)
        {
            T* temp[size];
            *temp = content;
            size += step;
            content = new T[size];
            for (int i = 0; i <= size - step; i++)
            {
                content[i] = *temp[i];
            }
            for (int i = size; i > fill ; i--)
            {
                content[i] = NULL;
            }
            if (has_limit)
                std::cout << "Size changed! Exceeded preset limit! New limit: " << size << std::endl;
            
            return;
        }
        std::cout << "There is no more space in here! Use table.set() instead of table.add()!!" << std::endl;
    }
    
    void print()
    {
        int w = 0;
        for (int i = 0; i < getSize(); i++)
        {
            {
                std::cout << at(i) << " <- " << i << ", ";
                if (w > 0)
                {
                    std::cout << std::endl;
                    w = -1;
                }
                w++;
            }
        }
        std::cout << "size was: " << getSize() << std::endl;
    }
};
