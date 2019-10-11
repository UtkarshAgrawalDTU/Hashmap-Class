#include<iostream>
#include<string.h>

using namespace std;

template<typename V>
class MapNode{

    public:

        string key;
        V value;
        MapNode *next;

        MapNode(string key, V value) : key(key), value(value), next(NULL)
        {}

        ~MapNode()
        {
            delete next;
        }
};




template<typename V>
class ourmap{

    MapNode<V> **buckets;
    int counts;
    int numBuckets;


    void rehash()
    {
        MapNode <V> ** temp = buckets;

        buckets = new MapNode <V>*[2*numBuckets];

        for(int i =0; i< 2 * numBuckets; i++)
            buckets[i] = NULL;

        int oldBucketsCount = numBuckets;
        numBuckets *= 2;

        for(int i = 0; i < oldBucketsCount; i++)
        {
            MapNode<V> * ptr = temp[i];

            while(ptr)
            {
                inserts(ptr->key, ptr->value);
                ptr = ptr->next;
            }
        }

        for(int i = 0; i < oldBucketsCount; i++)
            delete temp[i];

        delete [] temp;
    }

    public:

        ourmap() : counts(0), numBuckets(5)
        {
            buckets = new MapNode<V> *[numBuckets];

            for(int i = 0; i<numBuckets; i++)
                buckets[i] = NULL;
        }



        ~ourmap()
        {
            for(int i =0; i<numBuckets; i++)
                delete buckets[i];

            delete [] buckets;
        }



        double loadfactor()
        {
            return 1.0*counts/numBuckets;
        }



        int getBucketIndex(string key)
        {
            int index = 1;
            int pno = 37;

            for(int i = key.size()-1; i>=0; i--)
            {
                index = index + key[i]*pno;
                index = index % numBuckets;
                pno *= pno;
                pno = pno % numBuckets;
            }

            return index%numBuckets;
        }




        void inserts(string key, V val)
        {
            int index = getBucketIndex(key);
            MapNode <V> * ptr = buckets[index];

            while(ptr)
            {
                if(ptr->key == key)
                {
                    ptr->value = val;
                    return;
                }
                ptr = ptr->next;
            }

            ptr = buckets[index];
            MapNode <V> *temp = new MapNode<V>(key, val);
            temp->next = ptr;
            buckets[index] = temp;
            counts++;

            double lf = loadfactor();

            if(lf > 0.7)
                rehash();
        }




        int sizes()
        {
            return counts;
        }




        V deletes(string key)
        {
            int index = getBucketIndex(key);
            MapNode <V> *ptr = buckets[index], *prev = NULL;

            while(ptr)
            {
                if(ptr->key == key)
                {
                    if(prev == NULL)
                    {
                        V val = ptr->value;
                        buckets[index] = ptr->next;
                        ptr->next = NULL;
                        delete ptr;
                        counts--;
                        return val;
                    }

                    V val = ptr->value;
                    prev->next = ptr->next;
                    ptr->next = NULL;
                    counts--;
                    delete ptr;
                    return val;
                }

                prev = ptr;
                ptr = ptr->next;
            }

            return 0;
        }




        V getvalue(string key)
        {
            int index = getBucketIndex(key);
            MapNode <V> *ptr = buckets[index];

            while(ptr)
            {
                if(ptr->key == key)
                    return ptr->value;
                ptr = ptr->next;
            }

            return 0;
        }


};

