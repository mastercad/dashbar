#ifndef __ISETTING_H__
#define __ISETTING_H__

#include <QHash>
#include <QString>

// template<typename T>
class ISetting
{
    /*
    public:
        virtual ~ISetting() {}
        virtual QString getIdentifier() = 0;
/*
         template<typename T> QHash<QString, T>* getKeys() {
            return keys;
        };
*//*
        const T* getKeys() const{ return keys;}
//        template<typename T> void add(const QString key, const T value) {keys->insert(key, value);}
        void add(const QString key, const T value) {keys->insert(key, value);}
    /*
    protected:
//        QHash<QString, QString>* keys;
        T keys;
        */
};
/*
template<class T> const T* ISetting::getKeys() const {
    return dymaic_cast<const ISetting<T>*>(this).getKeys();
}
*/
#endif
