#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Punto {
    int x, y;
    bool operator<(const Punto& otro) const {
        return tie(x, y) < tie(otro.x, otro.y);
    }
};

struct Segmento {
    Punto p1, p2;
    Segmento(Punto a, Punto b) : p1(a), p2(b) {
        if (p2 < p1) swap(p1, p2);
    }
};

struct Evento {
    int x;
    bool isStart;
    Segmento* segmento;
    
    bool operator<(const Evento& otro) const {
        if (x != otro.x)
            return x < otro.x;
        return isStart > otro.isStart;
    }
};

bool interseccion(const Segmento& s1, const Segmento& s2) {
    auto orientacion = [](const Punto& p, const Punto& q, const Punto& r) {
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0) return 0;
        return (val > 0) ? 1 : 2;
    };

    auto enSegmento = [](const Punto& p, const Punto& q, const Punto& r) {
        return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
                q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
    };

    int o1 = orientacion(s1.p1, s1.p2, s2.p1);
    int o2 = orientacion(s1.p1, s1.p2, s2.p2);
    int o3 = orientacion(s2.p1, s2.p2, s1.p1);
    int o4 = orientacion(s2.p1, s2.p2, s1.p2);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && enSegmento(s1.p1, s2.p1, s1.p2)) return true;
    if (o2 == 0 && enSegmento(s1.p1, s2.p2, s1.p2)) return true;
    if (o3 == 0 && enSegmento(s2.p1, s1.p1, s2.p2)) return true;
    if (o4 == 0 && enSegmento(s2.p1, s1.p2, s2.p2)) return true;

    return false;
}

struct compararSegmentos {
    bool operator()(const Segmento* s1, const Segmento* s2) const {
        if (s1->p1.y == s2->p1.y) return s1->p2.y < s2->p2.y;
        return s1->p1.y < s2->p1.y;
    }
};

bool detectarInterseccion(vector<Segmento>& segmentos) {
    vector<Evento> events;
    
    
    for (auto& segmento : segmentos) {
        events.push_back({segmento.p1.x, true, &segmento});
        events.push_back({segmento.p2.x, false, &segmento});
    }
    
    sort(events.begin(), events.end());

    set<Segmento*, compararSegmentos > activeSegments;

    // Sweep line
    for (auto& event : events) {
        Segmento* currentSegment = event.segmento;

        if (event.isStart) {
            auto iter = activeSegments.insert(currentSegment).first;
            
            auto above = next(iter);
            auto below = (iter == activeSegments.begin()) ? activeSegments.end() : prev(iter);

            if (above != activeSegments.end() && interseccion(**iter, **above)) return true;
            if (below != activeSegments.end() && interseccion(**iter, **below)) return true;
        } else {
            auto iter = activeSegments.find(currentSegment);
            auto above = next(iter);
            auto below = (iter == activeSegments.begin()) ? activeSegments.end() : prev(iter);

            if (above != activeSegments.end() && below != activeSegments.end() && interseccion(**above, **below)) return true;

            activeSegments.erase(iter);
        }
    }

    return false;
}
