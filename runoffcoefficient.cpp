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

#include "runoffcoefficient.h"

using namespace std;

RunoffCoefficient::RunoffCoefficient()
{
    // Initialize the list of the parameter "k"
    list_k = { {0.26, 0.28, 0.30},
          {0.24, 0.27, 0.30},
          {0.24, 0.27, 0.30},
          {0.14, 0.20, 0.28},
          {0.20, 0.24, 0.30},
          {0.24, 0.28, 0.30},
          {0.07, 0.16, 0.24},
          {0.12, 0.22, 0.26},
          {0.17, 0.26, 0.28},
          {0.22, 0.28, 0.30},
          {0.26, 0.29, 0.32},
          {0.27, 0.30, 0.33},
          {0.18, 0.24, 0.30}
      };
}

std::vector<float> RunoffCoefficient::getAreas() const
{
    return areas;
}

void RunoffCoefficient::setAreas(const std::vector<float> &value)
{
    areas = value;
}

std::vector<int> RunoffCoefficient::getLanduses() const
{
    return landuses;
}

void RunoffCoefficient::setLanduses(const std::vector<int> &value)
{
    landuses = value;
}

std::vector<int> RunoffCoefficient::getSoiltypes() const
{
    return soiltypes;
}

void RunoffCoefficient::setSoiltypes(const std::vector<int> &value)
{
    soiltypes = value;
}

float RunoffCoefficient::getPrecipitation() const
{
    return precipitation;
}

void RunoffCoefficient::setPrecipitation(float value)
{
    precipitation = value;
}

float RunoffCoefficient::getRunoffCoefficient() const
{
    return runoffCoefficient;
}

void RunoffCoefficient::calculate()
{

    area = 0;        // Total area of the watershed
    float ka;        // A "k" parameter for each sub-area
    float karea = 0;  // Sum of k*area
    float k;         // The "k" parameter
    for (int i = 0; i < int(areas.size()); i++) {
        // Get the "k" parameter from table for each soil type and land use
        ka = list_k[landuses.at(i)][soiltypes.at(i)];
        // Multiply the "k" values with their corresponding area
        karea = karea + (ka * areas.at(i));

        area = area + areas.at(i);
    }
    // Get the weighted sum
    k = karea / area;

    // Finally get the runoff coefficient
    if (k <= 0.15) {
        runoffCoefficient = k * (precipitation - 250) / 2000;
    } else {
        runoffCoefficient = k * (precipitation - 250) / 2000 + (k - 0.15) / 1.5;
    }
}
