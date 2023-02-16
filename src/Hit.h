/*
 * Project: MutomcaReader
 * File:    Hit.h
 * Author:  Altea Lorenzon < altea.lorenzon@pd.infn.it >
 *
 * Created on February 16, 2023
 */

#ifndef HIT_H
#define HIT_H

class Hit {
public:
    Hit();
    ~Hit();

    void setBoardID(int board);
    void setChID(int ch);
    void setLayID(int layer);
    void setCellID(int cell);
    void setRawTime(float rtime);

    int getBoardID();
    int getChID();
    int getLayID();
    int getCellID();
    float getRawTime();

private:
    int _boardID;
    int _chID;
    int _layID;
    int _cellID;
    float _rawtime;

};

#endif
