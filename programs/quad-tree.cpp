#include <iostream>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

class QuadTree {
public:
    QuadTree(float lat, float lon, int level) : _lat(lat), _lon(lon), _curLevel(level) {
    }

    void split() { // generate children
        if (_curLevel > _targetLevel) return;
        _child = make_shared<QuadTree>(_lat, _lon, _curLevel + 1);
        float midLat = _lat < _minp.first + (_maxp.first - _minp.first) /2;
        float midLon = _lon < _minp.second + (_maxp.second - _minp.second) / 2;
        if (_curLevel == 0) {
            if (_lon >= _minp.second && _lon < midLon) { // left
                _child->setMin(_minp.first, _minp.second);
                _child->setMax(_maxp.first, midLon);
                _child->_val = 0;
            } else { // right
                _child->setMin(_minp.first, midLon);
                _child->setMax(_maxp.first, _maxp.second);
                _child->_val = 1;
            }
        } else if (_curLevel == 1) {
            if (_lat >= _minp.first && _lat < midLat) { // bottom
                _child->setMin(_minp.first, _minp.second);
                _child->setMax(midLat, _maxp.second);
                _child->_val = 3 - _val;
            } else { // upper
                _child->setMin(midLat, _minp.second);
                _child->setMax(_maxp.first, _maxp.second);
                _child->_val = _val;
            }
        } else {
            if (_lat >= _minp.first && _lat < midLat && _lon >= _minp.second && _lon < midLon) { // left bottom
                _child->setMin(_minp.first, _minp.second);
                _child->setMax(midLat, midLon);
                _child->_val = 3;
            }
        }
        _child->setLevel(_targetLevel);
    }

    void setLevel(int level) {
        _targetLevel = level;
        split();
    }

    void print() {
        if (_curLevel > 0) cout << _val;
        if (_child) _child->print();
    }

protected:
    float _lat;
    float _lon;
    int _val = 0;
    pair<float, float> _minp {-90, -180};
    pair<float, float> _maxp {90, 180};
    int _curLevel;
    int _targetLevel;
    const int limit = 32;
    shared_ptr<QuadTree> _child;

    void setMin(float lat, float lon) {
        _minp.first = lat;
        _minp.second = lon;
    }

    void setMax(float lat, float lon) {
        _maxp.first = lat;
        _maxp.second = lon;
    }
};

int main() {
    shared_ptr<QuadTree> ptr = make_shared<QuadTree>(37.450447, -122.123033, -1);
    int level;
    cout << "Input level: " << endl;
    cin >> level;
    ptr->setLevel(level);
    ptr->print();
    return -1;
}

// Write a function to generate the quadtree code of a given latitude
// and longitude at a given level.

// E.g., lat 37.450447, lon -122.123033, level 16 -> 00310203130232300
//     lat 37.450447, lon -122.123033, level 5 -> 003102


// Latitude can range from -90 to 90, longitude from -180 to 180

// Max level is 32

//  _____________________________
//  |             |             |
//  |             |             |
//  |             |             |
//  |             |             |
//  |             |             |
//  |             |             |
//  |      0      |      1      |
//  |             |             |
//  |             |             |
//  |             |             |
//  |             |             |
//  |             |             |
//  |             |             |
//  |_____________|_____________|


// -180 lon            180 lon
// _____________________________
// |      |      |             |    90 lat
// |  00  |  01  |             |
// |      |      |             |
// |---\---0------|      1      |
// |030\031|      |             |
// |  03   |  02  |             |
// |033\032|______|_____________|
// |             |             |
// |             |             |
// |             |             |
// |      3      |      2      |
// |             |             |
// |             |             |
// |_____________|_____________| -90 lat