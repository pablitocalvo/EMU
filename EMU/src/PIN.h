/*
 * PIN.h
 *
 *  Created on: 27/feb/2019
 *      Author: paolo
 */

#ifndef PIN_H_
#define PIN_H_

class PIN
{
public:
    PIN()
    {
        stato='-';
        valore = false;
    }
    virtual
    ~PIN();

private:

    bool valore;
    char stato;

    bool
    getValore() const
    {
        return valore;
    }

    void
    setValore(bool valore)
    {
        this->valore = valore;
    }

};

#endif /* PIN_H_ */
