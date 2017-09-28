/*
 * Cálculo del coeficiente de escurrimiento de acuerdo a la norma oficial
 * mexicana NOM-011-CONAGUA-2015, Conservación del recurso agua.
 * Copyright (C) 2017 Eduardo Jiménez
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#ifndef RUNOFFCOEFFICIENT_H
#define RUNOFFCOEFFICIENT_H

#include <vector>

class RunoffCoefficient
{
public:
    RunoffCoefficient();
    std::vector<float> getAreas() const;
    void setAreas(const std::vector<float> &value);

    std::vector<int> getLanduses() const;
    void setLanduses(const std::vector<int> &value);

    std::vector<int> getSoiltypes() const;
    void setSoiltypes(const std::vector<int> &value);

    float getPrecipitation() const;
    void setPrecipitation(float value);

    float getRunoffCoefficient() const;

    void calculate();
private:
    std::vector< std::vector<float> > list_k;
    std::vector<float> areas;
    std::vector<int> landuses;
    std::vector<int> soiltypes;
    float precipitation;
    float area;
    float runoffCoefficient;


};

#endif // RUNOFFCOEFFICIENT_H
