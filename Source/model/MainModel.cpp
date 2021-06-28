/*
  ==============================================================================

    MainModel.cpp
    Created: 27 Jun 2021 10:05:23pm
    Author:  Toko

  ==============================================================================
*/

#include "MainModel.h"

MainModel::MainModel()
{
}

MainModel::~MainModel()
{
}

void MainModel::TestFunction()
{
    this->test = true;
}

bool MainModel::GetTest()
{
    return test;
}
