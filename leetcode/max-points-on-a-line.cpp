#include <vector>
#include <math.h>
#include <limits>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <stdio.h>

struct Vector {
    double x;
    double y;
    Vector() : x(0), y(0) {}
    Vector(double a, double b) : x(a), y(b) {}

    bool operator > (const Vector& v) const
    {
        if (abs(this->x - v.x) < numeric_limits<double>::epsilon()) {
            //printf("y:%lf-%lf\n", this->y, v.y);
            return this->y > v.y;
        }


        //printf("x:%lf-%lf\n", this->x, v.x);
        return this->x > v.x;
    }
};

class Solution {
public:
    void getNormal(Point &a, Point &b, Vector &norm) {
        double deltaX = a.x - b.x;
        double deltaY = a.y - b.y;
        double length = sqrt(pow(deltaY, 2) + pow(deltaX, 2));
        norm.x = deltaX != 0 ? deltaX / length : 0;
        norm.y = deltaY != 0 ? deltaY / length : 0;
    }

    int maxPoints(vector<Point> &points) {
        if (points.size() < 3) {
            return points.size();
        }
        int max = 0;
        unordered_map<int, unordered_map<int, vector<Vector>>> slopsHash;
        unordered_map<int, unordered_map<int, int>> dups;
        Vector v;
        for (int i = 0; i < points.size(); ++i) {
            dups[points[i].x][points[i].y]++;
            if (dups[points[i].x][points[i].y] > 1) {
                continue;
            }

            for (int j = i + 1; j < points.size(); ++j) {
                if (points[i].x == points[j].x && points[i].y == points[j].y) {
                    continue;
                }

                getNormal(points[i], points[j], v);
                if (v.x < 0) {
                    v.x *= -1;
                    v.y *= -1;
                }

                if (v.x == 0) {
                    v.y = abs(v.y);
                }

                slopsHash[points[i].x][points[i].y].push_back(v);
            }
        }

        Vector u;
        vector<Vector> slops;
        for (Point p : points) {
            int cmax = dups[p.x][p.y];
            slops = slopsHash[p.x][p.y];
            if (slops.empty()) {
                max = std::max(cmax, max);
                continue;
            }
            cmax -= 1;
            std::sort(slops.begin(), slops.end(), greater<Vector>());
            Vector w = slops[0];
            cmax += 2;
            max = std::max(cmax, max);
            for (int j = 1; j < slops.size(); ++j)
            {
                u = slops[j];
                if (abs(w.x - u.x) < numeric_limits<double>::epsilon() &&
                    abs(w.y - u.y) < numeric_limits<double>::epsilon()) {
                    cmax++;
                }
                else {
                    w = u;
                    cmax = 2;
                }
                max = std::max(cmax, max);
            }
        }

        return max;
    }
};