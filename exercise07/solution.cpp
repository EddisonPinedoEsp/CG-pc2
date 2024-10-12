#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Estructura para representar un punto
template <typename T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}
};

// Estructura para representar un segmento
template <typename T>
struct Segment {
    Point<T> p1, p2;
    Segment(Point<T> p1, Point<T> p2) : p1(p1), p2(p2) {}

    // Devuelve el valor de y en el segmento en una posición x dada
    T get_y_at(T x) const {
        if (p1.x == p2.x) return p1.y; // segmento vertical
        return p1.y + (T)(p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
    }
};

// Evento para el barrido
template <typename T>
struct Event {
    T x;
    int segmentIndex;
    bool isStart;

    Event(T x, int segmentIndex, bool isStart) : x(x), segmentIndex(segmentIndex), isStart(isStart) {}

    // Ordena eventos por coordenada x, y en caso de empate, y eventos de inicio antes que los de final
    bool operator<(const Event& other) const {
        if (x == other.x) return isStart && !other.isStart;
        return x < other.x;
    }
};

// Función para determinar la orientación de tres puntos
template <typename T>
int orientation(const Point<T>& p, const Point<T>& q, const Point<T>& r) {
    T val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // colineal
    return (val > 0) ? 1 : 2; // 1: horario, 2: antihorario
}

// Función para determinar si dos segmentos se intersectan
template <typename T>
bool segments_intersect(const Segment<T>& s1, const Segment<T>& s2) {
    Point<T> p1 = s1.p1, q1 = s1.p2, p2 = s2.p1, q2 = s2.p2;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // Caso general
    if (o1 != o2 && o3 != o4)
        return true;

    // Casos especiales
    if (o1 == 0 && on_segment(p1, p2, q1)) return true;
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;

    return false;
}

// Verifica si el punto q está en el segmento pr
template <typename T>
bool on_segment(const Point<T>& p, const Point<T>& q, const Point<T>& r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

// Función principal que decide si existen intersecciones
template <typename T>
bool exist_intersections(const vector<vector<T>>& segments) {
    int n = segments.size();
    vector<Segment<T>> segs;

    // Convertir los segmentos en la estructura de Segment y eventos de inicio y fin
    vector<Event<T>> events;
    for (int i = 0; i < n; ++i) {
        Point<T> p1(segments[i][0], segments[i][1]);
        Point<T> p2(segments[i][2], segments[i][3]);

        if (p1.x > p2.x) swap(p1, p2); // Asegurar que p1 está a la izquierda de p2

        segs.push_back(Segment<T>(p1, p2));
        events.push_back(Event<T>(p1.x, i, true));  // Evento de inicio
        events.push_back(Event<T>(p2.x, i, false)); // Evento de fin
    }

    // Ordenar los eventos por la coordenada x
    sort(events.begin(), events.end());

    // Estructura para almacenar los segmentos activos
    set<int> activeSegments;

    // Función lambda para comparar segmentos por su posición en la línea de barrido
    auto compare = [&](int i, int j) {
        T x = events[i].x;
        return segs[i].get_y_at(x) < segs[j].get_y_at(x);
    };

    // Procesar los eventos
    for (const auto& event : events) {
        int index = event.segmentIndex;

        if (event.isStart) {
            // Insertar el segmento en la lista activa
            auto it = activeSegments.insert(index).first;

            // Comprobar si se intersecta con el anterior y siguiente
            if (it != activeSegments.begin() && segments_intersect(segs[index], segs[*prev(it)]))
                return true;
            if (next(it) != activeSegments.end() && segments_intersect(segs[index], segs[*next(it)]))
                return true;
        } else {
            // Eliminar el segmento de la lista activa
            auto it = activeSegments.find(index);
            if (it != activeSegments.begin() && next(it) != activeSegments.end() &&
                segments_intersect(segs[*prev(it)], segs[*next(it)]))
                return true;
            activeSegments.erase(it);
        }
    }

    return false; // No se encontraron intersecciones
}

bool exist_intersections(const vector<vector<int>>& segments) {
    return exist_intersections<int>(segments);
}

bool exist_intersections(const vector<vector<double>>& segments) {
    return exist_intersections<double>(segments);
}