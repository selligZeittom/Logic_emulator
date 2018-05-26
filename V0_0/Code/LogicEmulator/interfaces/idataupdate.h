#ifndef IUPDATE_H
#define IUPDATE_H


class IDataUpdate
{
public:
    IDataUpdate();
    virtual void onDataChanged() = 0;
};

#endif // IUPDATE_H
