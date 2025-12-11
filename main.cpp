#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <climits>
#include <sstream>
#include <math.h>
#include<cctype>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

// helper func
string allLower(string input)
{
    for(int i = 0; i != input.length(); i++)
    {
        input[i] = tolower((unsigned char)input[i]);
    }
    return input;
}



// ======================= DSA CLASSES =======================

class TimeNode
{
public:
    int time;
    TimeNode* left;
    TimeNode* right;

    TimeNode(int t) : time(t), left(NULL), right(NULL) {}
};

class RouteSchedule
{
private:
    string routeName;
    TimeNode* root;

    TimeNode* insertTime(TimeNode* node, int t)
    {
        if(node == NULL)
        {
            node = new TimeNode(t);
            return node;
        }

        if(node->time > t)
            node->left = insertTime(node->left, t);
        else if(node->time < t)
            node->right = insertTime(node->right, t);

        return node;
    }

    void inorderPrint(TimeNode* node)
    {
        if(node == NULL)
            return;

        inorderPrint(node->left);
        cout << node->time << " ";
        inorderPrint(node->right);
    }

    TimeNode* findMinNode(TimeNode* node)
    {
        if(node == NULL) return NULL;

        while(node->left != NULL)
            node = node->left;
        return node;
    }

    TimeNode* findMaxNode(TimeNode* node)
    {
        if(node == NULL) return NULL;

        while(node->right != NULL)
            node = node->right;
        return node;
    }

    TimeNode* deleteTime(TimeNode* node, int t)
    {
        if(node == NULL) return NULL;

        if(t < node->time)
            node->left = deleteTime(node->left, t);
        else if(t > node->time)
            node->right = deleteTime(node->right, t);
        else
        {
            if(node->left == NULL && node->right == NULL)
            {
                delete node;
                return NULL;
            }

            if(node->left == NULL && node->right != NULL)
            {
                TimeNode* temp = node->right;
                delete node;
                return temp;
            }

            if(node->left != NULL && node->right == NULL)
            {
                TimeNode* temp = node->left;
                delete node;
                return temp;
            }

            TimeNode* succ = findMinNode(node->right);
            node->time = succ->time;
            node->right = deleteTime(node->right, succ->time);
        }
        return node;
    }

    int countNodes(TimeNode* node)
    {
        if(node == NULL)
        {
            return 0;
        }
        int leftCount = countNodes(node->left);
        int rightCount = countNodes(node->right);
        return 1 + leftCount + rightCount;
    }

public:
    RouteSchedule(string name = "") : routeName(name), root(NULL) {}

    void setRouteName(string name) { routeName = name;}
    string getRouteName() { return routeName; }
    bool isEmpty() { return root == NULL;}

    void addDeparture(int t)
    {
        root = insertTime(root, t);
    }

    void printSchedule()
    {
        cout << "Schedule for route: " << routeName << endl;
        if(root == NULL)
        {
            cout << "No departures added yet." << endl;
            return;
        }
        inorderPrint(root);
        cout << endl;
    }

    int findNextDeparture(int currentTime)
    {
        TimeNode* temp = root;
        int nextTime = -1;

        while(temp != NULL)
        {
            if(currentTime < temp->time)
            {
                nextTime = temp->time;
                temp = temp->left;
            }
            else
                temp = temp->right;
        }

        return nextTime;
    }

    int getEarliestDeparture()
    {
        TimeNode* minNode = findMinNode(root);
        if(minNode == NULL)
            return -1;
        return minNode->time;
    }

    int getLatestDeparture()
    {
        TimeNode* maxNode = findMaxNode(root);
        if(maxNode == NULL)
            return -1;
        return maxNode->time;
    }

    void removeDeparture(int t) { root = deleteTime(root, t); }
    int getTotalDepartures() { return countNodes(root); }
};

class RouteManager
{
private:
    RouteSchedule* routes;
    int routeCount;
    int capacity;

    int findRouteIndex(string name)
    {
        name = allLower(name);
        for(int i = 0; i < routeCount; i++)
        {
            if(allLower(routes[i].getRouteName()) == name)
            {
                return i;
            }
        }
        return -1;
    }

public:
    RouteManager(int maxRoutes)
    {
        capacity = maxRoutes;
        routeCount = 0;
        routes = new RouteSchedule[capacity];
    }

    ~RouteManager()
    {
        delete[] routes;
    }

    void addRoute(string name)
    {
        if(routeCount == capacity)
        {
            cout << "Cannot add more routes (capacity full)." << endl;
            return;
        }

        if(findRouteIndex(name) != -1)
        {
            cout << "Route with this name already exists." << endl;
            return;
        }

        routes[routeCount].setRouteName(name);
        routeCount++;
        cout << "Route \"" << name << "\" added successfully." << endl;
    }

    void addDepartureToRoute(string name, int time)
    {
        int index = findRouteIndex(name);
        if(index == -1 )
        {
            cout << "Route not found." << endl;
            return;
        }

        routes[index].addDeparture(time);
        cout << "Added departure " << time << " to route " << name << "." << endl;
    }

    void printRouteSchedule(string name)
    {
        int idx = findRouteIndex(name);
        if(idx == -1)
        {
            cout << "Route not found." << endl;
            return;
        }

        routes[idx].printSchedule();
    }

    void printAllRoutes()
    {
        if(routeCount == 0)
        {
            cout << "No routes added yet." << endl;
            return;
        }

        cout << "Available routes:" << endl;
        for(int i = 0; i < routeCount; i++)
        {
            cout << "- " << routes[i].getRouteName() << endl;
        }
    }

    void findNextDepartureOnRoute(string name, int currentTime)
    {
        int idx = findRouteIndex(name);
        if(idx == -1)
        {
            cout << "Route not found." << endl;
            return;
        }

        if(routes[idx].isEmpty())
        {
            cout << "No departures available for this route." << endl;
            return;
        }

        int nextTime = routes[idx].findNextDeparture(currentTime);

        if(nextTime == -1)
        {
            cout << "No more buses on route " << name
                 << " after " << currentTime << "." << endl;
        }
        else
        {
            cout << "Next bus on route " << name
                 << " after " << currentTime
                 << " is at: " << nextTime << endl;
        }
    }
};

class EdgeInfo
{
public:
    int travelTime;
    int travelCost;
    string routeName;
    bool exists;

    EdgeInfo() : travelTime(0), travelCost(0), routeName(""), exists(false) {}
};

class MinHeap
{
private:
    int* heapArr;
    int* pos;
    int size;
    int capacity;

    void swapNodes(int i, int j)
    {
        int v1 = heapArr[i];
        int v2 = heapArr[j];
        heapArr[i] = v2;
        heapArr[j] = v1;
        pos[v1] = j;
        pos[v2] = i;
    }

    void heapifyUp(int idx, int dist[])
    {
        while(idx > 0)
        {
            int parent = (idx - 1)/2;
            if(dist[heapArr[idx]] < dist[heapArr[parent]])
            {
                swapNodes(idx, parent);
                idx = parent;
            }
            else
                break;
        }
    }

    void heapifyDown(int idx, int dist[])
    {
        while(true)
        {
            int left =  2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;

            if(left < size && dist[heapArr[left]] < dist[heapArr[smallest]])
                smallest = left;
            if(right < size && dist[heapArr[right]] < dist[heapArr[smallest]])
                smallest = right;
            if(smallest != idx)
            {
                swapNodes(idx, smallest);
                idx = smallest;
            }
            else
                break;
        }
    }

public:
    MinHeap(int cap, int vertexCount)
    {
        capacity = cap;
        size = 0;
        heapArr = new int[capacity];
        pos = new int[vertexCount];
        for(int i = 0; i < vertexCount; i++)
            pos[i] = -1;
    }

    ~MinHeap()
    {
        delete[] heapArr;
        delete[] pos;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    bool isInHeap(int v)
    {
        return pos[v] != -1;
    }

    void insert(int v, int dist[])
    {
        if(size == capacity)
            return;
        heapArr[size] = v;
        pos[v] = size;
        heapifyUp(size, dist);
        size++;
    }

    int extractMin(int dist[])
    {
        if(size == 0)
            return -1;
        int rootVertex = heapArr[0];
        heapArr[0] = heapArr[size - 1];
        pos[heapArr[0]] = 0;
        pos[rootVertex] = -1;
        size--;
        heapifyDown(0, dist);
        return rootVertex;
    }

    void decreaseKey(int v, int dist[])
    {
        int idx = pos[v];
        if(idx == -1)
            return;
        heapifyUp(idx, dist);
    }
};

class Graph
{
private:
    int maxVertices;
    int vertexCount;
    string* stopNames;
    EdgeInfo** adjMatrix;

    int getIndexOfStop(string name)
    {
        name = allLower(name);
        for(int i = 0; i < vertexCount; i++)
        {
            if(allLower(stopNames[i]) == name)
            {
                return i;
            }
        }
        return -1;
    }

public:
    Graph(int maxV)
    {
        maxVertices = maxV;
        vertexCount = 0;

        stopNames = new string[maxVertices];

        adjMatrix = new EdgeInfo*[maxVertices];
        for(int i = 0; i < maxVertices; i++)
            adjMatrix[i] = new EdgeInfo[maxVertices];
    }

    ~Graph()
    {
        for(int i = 0; i < maxVertices; i++)
        {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;

        delete[] stopNames;
    }

    void addStop(string name)
    {
        if(vertexCount == maxVertices)
        {
            cout << "Cannot add more stops (capacity full)." << endl;
            return;
        }

        if(getIndexOfStop(name) != -1)
        {
            cout << "Stop \"" << name << "\" already exists." << endl;
            return;
        }

        stopNames[vertexCount] = name;
        vertexCount++;

        cout << "Stop \"" << name << "\" added successfully." << endl;
    }

    void addConnection(string from, string to, int time, int cost, string routeName)
    {
        int fromIndex = getIndexOfStop(from);
        int toIndex = getIndexOfStop(to);

        if(fromIndex == -1 || toIndex == -1)
        {
            cout << "One or both stops not found: " << from << ", " << to << endl;
            return;
        }

        adjMatrix[fromIndex][toIndex].travelTime = time;
        adjMatrix[fromIndex][toIndex].travelCost = cost;
        adjMatrix[fromIndex][toIndex].routeName = routeName;
        adjMatrix[fromIndex][toIndex].exists = true;

        cout << "Connection added for route " << routeName << ": " << from << " -> " << to
             << " (" << time << " min, Rs." << cost << ")" << endl;
    }

    void printStops()
    {
        cout << "Stops in the city:\n";
        for(int i = 0; i < vertexCount; i++)
        {
            cout << "  " << i << ") " << stopNames[i] << "\n";
        }
        cout << "\n";
    }

    void printAdjacencyMatrix()
    {
        if (vertexCount == 0) {
            cout << "No stops in the graph.\n\n";
            return;
        }

        cout << "Adjacency Matrix (time/cost, '-' = no route):\n\n";

        const int NAMEW = 15;  // Width for stop names
        const int CELLW = 10;  // Width for cells

        // Print header row
        cout << left << setw(NAMEW) << "";
        for (int j = 0; j < vertexCount; j++)
            cout << left << setw(CELLW) << stopNames[j];
        cout << "\n";

        // Print separator line
        cout << string(NAMEW + (vertexCount * CELLW), '-') << "\n";

        // Print each row
        for (int i = 0; i < vertexCount; i++)
        {
            cout << left << setw(NAMEW) << stopNames[i];

            for (int j = 0; j < vertexCount; j++)
            {
                if (adjMatrix[i][j].exists)
                {
                    string cell = to_string(adjMatrix[i][j].travelTime) + "/" +
                                  to_string(adjMatrix[i][j].travelCost);
                    cout << left << setw(CELLW) << cell;
                }
                else
                {
                    cout << left << setw(CELLW) << "-";
                }
            }
            cout << "\n";
        }

        cout << "\n";
    }

    void printRoutePath(string routeName)
    {
        cout << "Path for route: " << routeName << endl;
        bool found = false;

        for(int i = 0; i < vertexCount; i++)
        {
            for(int j = 0; j < vertexCount; j++)
            {
                if(adjMatrix[i][j].exists && allLower(adjMatrix[i][j].routeName) == routeName)
                {
                    cout << stopNames[i] << " -> " << stopNames[j]
                         << " (" << adjMatrix[i][j].travelTime
                         << " min, Rs." << adjMatrix[i][j].travelCost << ")\n";
                    found = true;
                }
            }
        }

        if(!found)
        {
            cout << "No edges found for this route.\n";
        }
    }

    void shortestPathByTime(string source, string dest)
    {
        int srcIdx = getIndexOfStop(source);
        int destIdx = getIndexOfStop(dest);

        if(srcIdx == -1 || destIdx == -1)
        {
            cout << "Source or destination stop not found." << endl;
            return;
        }

        int* dist = new int[vertexCount];
        int* parent = new int[vertexCount];

        for(int i = 0; i < vertexCount; i++)
        {
            dist[i] = INT_MAX;
            parent[i] = -1;
        }

        dist[srcIdx] = 0;

        MinHeap heap(vertexCount, vertexCount);

        for(int v = 0; v < vertexCount; v++)
        {
            heap.insert(v, dist);
        }

        while(!heap.isEmpty())
        {
            int u = heap.extractMin(dist);
            if(u == -1)
            {
                break;
            }

            if(dist[u] == INT_MAX)
            {
                break;
            }

            if(u == destIdx)
            {
                break;
            }

            for(int v = 0; v < vertexCount; v++)
            {
                if(adjMatrix[u][v].exists)
                {
                    int w = adjMatrix[u][v].travelTime;

                    if(dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        parent[v] = u;

                        if(heap.isInHeap(v))
                        {
                            heap.decreaseKey(v, dist);
                        }
                    }
                }
            }
        }

        if(dist[destIdx] == INT_MAX)
        {
            cout << "No path found from " << source << " to " << dest << "." << endl;
        }
        else
        {
            cout << "\nShortest travel time from " << source << " to " << dest
                 << " is: " << dist[destIdx] << " minutes." << endl;

            int* path = new int[vertexCount];
            int count = 0;
            int curr = destIdx;

            while(curr != -1)
            {
                path[count++] = curr;
                curr = parent[curr];
            }

            cout << "Path: ";
            for(int i = count - 1; i >= 0; i--)
            {
                cout << stopNames[path[i]];
                if(i != 0)
                {
                    cout << " -> ";
                }
            }
            cout << endl;

            delete[] path;
        }

        delete[] dist;
        delete[] parent;
    }

    void shortestPathByCost(string source, string dest)
    {
        int srcIdx = getIndexOfStop(source);
        int destIdx = getIndexOfStop(dest);

        if(srcIdx == -1 || destIdx == -1)
        {
            cout << "Source or destination stop not found." << endl;
            return;
        }

        int* dist = new int[vertexCount];
        int* parent = new int[vertexCount];

        for(int i = 0; i < vertexCount; i++)
        {
            dist[i] = INT_MAX;
            parent[i] = -1;
        }

        dist[srcIdx] = 0;

        MinHeap heap(vertexCount, vertexCount);

        for(int v = 0; v < vertexCount; v++)
        {
            heap.insert(v, dist);
        }

        while(!heap.isEmpty())
        {
            int u = heap.extractMin(dist);
            if(u == -1)
            {
                break;
            }

            if(dist[u] == INT_MAX)
            {
                break;
            }

            if(u == destIdx)
            {
                break;
            }

            for(int v = 0; v < vertexCount; v++)
            {
                if(adjMatrix[u][v].exists)
                {
                    int w = adjMatrix[u][v].travelCost;

                    if(dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        parent[v] = u;

                        if(heap.isInHeap(v))
                        {
                            heap.decreaseKey(v, dist);
                        }
                    }
                }
            }
        }

        if(dist[destIdx] == INT_MAX)
        {
            cout << "No path found from " << source << " to " << dest << "." << endl;
        }
        else
        {
            cout << "\nCheapest travel cost from " << source << " to " << dest
                 << " is: Rs. " << dist[destIdx] << endl;

            int* path = new int[vertexCount];
            int count = 0;
            int curr = destIdx;

            while(curr != -1)
            {
                path[count++] = curr;
                curr = parent[curr];
            }

            cout << "Path: ";
            for(int i = count - 1; i >= 0; i--)
            {
                cout << stopNames[path[i]];
                if(i != 0)
                {
                    cout << " -> ";
                }
            }
            cout << endl;

            delete[] path;
        }

        delete[] dist;
        delete[] parent;
    }
};

class SmartCityTransportSystem
{
private:
    Graph cityGraph;
    RouteManager routeManager;
    bool dataInitialized;

public:
    SmartCityTransportSystem(int maxStops, int maxRoutes)
        : cityGraph(maxStops), routeManager(maxRoutes)
    {
        dataInitialized = false;
    }

    bool isDataInitialized()
    {
        return dataInitialized;
    }

    void setupDemoData()
    {
        if(dataInitialized)
        {
            cout << "Demo data is already initialized.\n";
            return;
        }

        cityGraph.addStop("Home");
        cityGraph.addStop("Mall");
        cityGraph.addStop("University");
        cityGraph.addStop("BusTerminal");
        cityGraph.addStop("Airport");
        cityGraph.addStop("Stadium");
        cityGraph.addStop("Hospital");

        routeManager.addRoute("GreenLine");
        routeManager.addRoute("AirportExpress");
        routeManager.addRoute("CityCircle");

        routeManager.addDepartureToRoute("GreenLine", 900);
        routeManager.addDepartureToRoute("GreenLine", 930);
        routeManager.addDepartureToRoute("GreenLine", 945);
        routeManager.addDepartureToRoute("GreenLine", 1030);

        routeManager.addDepartureToRoute("AirportExpress", 700);
        routeManager.addDepartureToRoute("AirportExpress", 745);
        routeManager.addDepartureToRoute("AirportExpress", 815);

        routeManager.addDepartureToRoute("CityCircle", 830);
        routeManager.addDepartureToRoute("CityCircle", 1000);
        routeManager.addDepartureToRoute("CityCircle", 1230);

        cityGraph.addConnection("Home",      "Mall",       10,  20, "GreenLine");
        cityGraph.addConnection("Mall",      "University", 15,  30, "GreenLine");
        cityGraph.addConnection("University","Stadium",    12,  25, "GreenLine");

        cityGraph.addConnection("BusTerminal","University", 25,  40, "AirportExpress");
        cityGraph.addConnection("University","Airport",     20,  50, "AirportExpress");

        cityGraph.addConnection("Home",     "Hospital",   8,   15, "CityCircle");
        cityGraph.addConnection("Hospital", "Mall",       7,   15, "CityCircle");
        cityGraph.addConnection("Mall",     "BusTerminal",18,  30, "CityCircle");
        cityGraph.addConnection("BusTerminal","Home",     22,  35, "CityCircle");

        dataInitialized = true;

        cout << "Demo data initialized successfully.\n";
    }

    void showRouteDetails(string routeName)
    {
        cout << "======================================\n";
        cout << "Route: " << routeName << "\n";
        cout << "======================================\n\n";

        cout << "[Departure Schedule]\n";
        routeManager.printRouteSchedule(routeName);
        cout << "\n[Route Path]\n";
        cityGraph.printRoutePath(routeName);

        cout << "======================================\n\n";
    }

    void showAllStopsAndMatrix()
    {
        cityGraph.printStops();
        cityGraph.printAdjacencyMatrix();
    }

    void testNextDeparture(string routeName, int currentTime)
    {
        cout << "\nNext departure on " << routeName << " after " << currentTime << ":\n";
        routeManager.findNextDepartureOnRoute(routeName, currentTime);
    }

    void testShortestTime(string source, string dest)
    {
        cout << "\n===== Shortest Path by TIME =====" << endl;
        cityGraph.shortestPathByTime(source, dest);
        cout << "================================" << endl;
    }

    void testCheapestCost(string source, string dest)
    {
        cout << "\n===== Cheapest Path by COST =====" << endl;
        cityGraph.shortestPathByCost(source, dest);
        cout << "================================" << endl;
    }

    void showAllRoutes()
    {
        routeManager.printAllRoutes();
    }
};

//          USER INTERFACE PART

#define ID_BTN_INIT          101
#define ID_BTN_STOPS_MATRIX  102
#define ID_BTN_ROUTES        103
#define ID_BTN_ROUTE_DETAILS 104
#define ID_BTN_NEXT_DEPART   105
#define ID_BTN_SHORTEST_TIME 106
#define ID_BTN_CHEAPEST_COST 107

#define ID_EDIT_OUTPUT       201
#define ID_EDIT_ROUTE        202
#define ID_EDIT_SOURCE       203
#define ID_EDIT_DEST         204
#define ID_EDIT_TIME         205

const int UI_MARGIN    = 10;
const int OUTPUT_TOPY  = 250;

SmartCityTransportSystem* g_system = NULL;
HWND g_hOutput     = NULL;
HWND g_hRouteEdit  = NULL;
HWND g_hSourceEdit = NULL;
HWND g_hDestEdit   = NULL;
HWND g_hTimeEdit   = NULL;

HFONT     g_hFont      = NULL;
HFONT     g_hMonoFont  = NULL;
HBRUSH    g_hBgBrush   = NULL;
HBRUSH    g_hOutputBg  = NULL;
HINSTANCE g_hInst      = NULL;

COLORREF g_mainBgColor   = RGB(245, 248, 252);
COLORREF g_outputBgColor = RGB(255, 255, 255);

std::ostringstream g_stream;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// --- helper functions for text edit ---

string GetEditText(HWND hEdit)
{
    char buffer[256];
    GetWindowTextA(hEdit, buffer, sizeof(buffer));
    return string(buffer);
}

void SetOutputText(const string& text)
{
    // Convert '\n' to "\r\n" for EDIT control
    std::string winText;
    winText.reserve(text.size() * 2);

    for(char c : text)
    {
        if(c == '\n')
            winText += "\r\n";
        else
            winText += c;
    }

    SetWindowTextA(g_hOutput, winText.c_str());
}

template<typename Func>
void RunWithCapturedOutput(Func func)
{
    g_stream.str("");
    g_stream.clear();

    std::streambuf* oldBuf = std::cout.rdbuf(g_stream.rdbuf());

    func();

    std::cout.rdbuf(oldBuf);

    SetOutputText(g_stream.str());
}

// ======================= WinMain =======================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    g_hBgBrush  = CreateSolidBrush(g_mainBgColor);
    g_hOutputBg = CreateSolidBrush(g_outputBgColor);

    WNDCLASSA wc = {};
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = g_hBgBrush;
    wc.lpszClassName = "SmartCityClass";

    g_hInst = hInstance;

    if(!RegisterClassA(&wc))
    {
        MessageBoxA(NULL, "Failed to register window class.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowExA(
        0,
        "SmartCityClass",
        "Smart City Transport System",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1300, 750,
        NULL, NULL, hInstance, NULL
    );

    if(!hwnd)
    {
        MessageBoxA(NULL, "Failed to create window.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    SmartCityTransportSystem system(20, 10);
    g_system = &system;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// ======================= UI creation =======================

void CreateUIControls(HWND hwnd)
{
    int margin = UI_MARGIN;
    int btnW = 180;
    int btnH = 30;

    g_hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

    g_hMonoFont = CreateFontA(
        20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, FF_DONTCARE | FIXED_PITCH, "Consolas");

    CreateWindowA("STATIC", "Smart City Transport System (DSA Project)",
        WS_CHILD | WS_VISIBLE,
        margin, margin, 400, 20,
        hwnd, NULL, NULL, NULL);

    HWND hBtnInit = CreateWindowA("BUTTON", "Initialize Demo Data",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        margin, margin + 30, btnW, btnH,
        hwnd, (HMENU)ID_BTN_INIT, NULL, NULL);

    HWND hBtnStops = CreateWindowA("BUTTON", "Show Stops + Matrix",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        margin + btnW + 10, margin + 30, btnW, btnH,
        hwnd, (HMENU)ID_BTN_STOPS_MATRIX, NULL, NULL);

    HWND hBtnRoutes = CreateWindowA("BUTTON", "Show All Routes",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        margin + 2*(btnW + 10), margin + 30, btnW, btnH,
        hwnd, (HMENU)ID_BTN_ROUTES, NULL, NULL);

    CreateWindowA("STATIC", "Route Name:",
        WS_CHILD | WS_VISIBLE,
        margin, margin + 80, 80, 20,
        hwnd, NULL, NULL, NULL);

    g_hRouteEdit = CreateWindowA("EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        margin + 90, margin + 80, 200, 22,
        hwnd, (HMENU)ID_EDIT_ROUTE, NULL, NULL);

    HWND hBtnRouteDetails = CreateWindowA("BUTTON", "Show Route Details",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        margin + 300, margin + 75, btnW, btnH,
        hwnd, (HMENU)ID_BTN_ROUTE_DETAILS, NULL, NULL);

    CreateWindowA("STATIC", "Current Time (e.g. 930):",
        WS_CHILD | WS_VISIBLE,
        margin, margin + 120, 160, 20,
        hwnd, NULL, NULL, NULL);

    g_hTimeEdit = CreateWindowA("EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        margin + 170, margin + 120, 120, 22,
        hwnd, (HMENU)ID_EDIT_TIME, NULL, NULL);

    HWND hBtnNextDepart = CreateWindowA("BUTTON", "Next Departure",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        margin + 300, margin + 115, btnW, btnH,
        hwnd, (HMENU)ID_BTN_NEXT_DEPART, NULL, NULL);

    CreateWindowA("STATIC", "Source Stop:",
        WS_CHILD | WS_VISIBLE,
        margin, margin + 170, 80, 20,
        hwnd, NULL, NULL, NULL);

    g_hSourceEdit = CreateWindowA("EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        margin + 90, margin + 170, 200, 22,
        hwnd, (HMENU)ID_EDIT_SOURCE, NULL, NULL);

    CreateWindowA("STATIC", "Destination:",
        WS_CHILD | WS_VISIBLE,
        margin, margin + 200, 80, 20,
        hwnd, NULL, NULL, NULL);

    g_hDestEdit = CreateWindowA("EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        margin + 90, margin + 200, 200, 22,
        hwnd, (HMENU)ID_EDIT_DEST, NULL, NULL);

    HWND hBtnShortest = CreateWindowA("BUTTON", "Shortest Time Path",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        margin + 300, margin + 165, btnW, btnH,
        hwnd, (HMENU)ID_BTN_SHORTEST_TIME, NULL, NULL);

    HWND hBtnCheapest = CreateWindowA("BUTTON", "Cheapest Cost Path",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        margin + 300, margin + 205, btnW, btnH,
        hwnd, (HMENU)ID_BTN_CHEAPEST_COST, NULL, NULL);

    // Output edit size
    RECT rc;
    GetClientRect(hwnd, &rc);
    int clientW = rc.right - rc.left;
    int clientH = rc.bottom - rc.top;

    int outX = margin;
    int outY = OUTPUT_TOPY;
    int outW = clientW - 2 * margin;
    int outH = clientH - OUTPUT_TOPY - margin;
    if (outH < 50) outH = 50;

    g_hOutput = CreateWindowA("EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER |
        ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL |
        WS_VSCROLL | WS_HSCROLL |
        ES_READONLY,
        outX, outY, outW, outH,
        hwnd, (HMENU)ID_EDIT_OUTPUT, NULL, NULL);

    // Set font on all controls
    HWND controls[] = {
        hBtnInit, hBtnStops, hBtnRoutes,
        g_hRouteEdit, hBtnRouteDetails,
        g_hTimeEdit, hBtnNextDepart,
        g_hSourceEdit, g_hDestEdit,
        hBtnShortest, hBtnCheapest
    };

    for(HWND c : controls)
    {
        if(c != NULL)
            SendMessage(c, WM_SETFONT, (WPARAM)g_hFont, TRUE);
    }

    // output box uses monospace font for matrix
    SendMessage(g_hOutput, WM_SETFONT, (WPARAM)g_hMonoFont, TRUE);
}

// ======================= WndProc =======================

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE:
        CreateUIControls(hwnd);
        break;

    case WM_COMMAND:
    {
        int id = LOWORD(wParam);

        if(!g_system)
            break;

        auto ensureData = [hwnd]() -> bool {
            if(!g_system->isDataInitialized())
            {
                MessageBoxA(hwnd, "Please initialize demo data first.", "Warning", MB_OK | MB_ICONWARNING);
                return false;
            }
            return true;
        };

        switch(id)
        {
        case ID_BTN_INIT:
        {
            RunWithCapturedOutput([]() {
                g_system->setupDemoData();
            });
            break;
        }

        case ID_BTN_STOPS_MATRIX:
        {
            if(!ensureData()) break;
            RunWithCapturedOutput([]() {
                g_system->showAllStopsAndMatrix();
            });
            break;
        }

        case ID_BTN_ROUTES:
        {
            if(!ensureData()) break;
            RunWithCapturedOutput([]() {
                g_system->showAllRoutes();
            });
            break;
        }

        case ID_BTN_ROUTE_DETAILS:
        {
            if(!ensureData()) break;
            string route = allLower(GetEditText(g_hRouteEdit));
            if(route.empty())
            {
                MessageBoxA(hwnd, "Enter a route name (e.g. GreenLine).", "Input Needed", MB_OK | MB_ICONINFORMATION);
                break;
            }
            RunWithCapturedOutput([route]() {
                g_system->showRouteDetails(route);
            });
            break;
        }

        case ID_BTN_NEXT_DEPART:
        {
            if(!ensureData()) break;
            string route = allLower(GetEditText(g_hRouteEdit));
            string timeStr = GetEditText(g_hTimeEdit);
            if(route.empty() || timeStr.empty())
            {
                MessageBoxA(hwnd, "Enter route name and current time.", "Input Needed", MB_OK | MB_ICONINFORMATION);
                break;
            }
            int t = atoi(timeStr.c_str());
            RunWithCapturedOutput([route, t]() {
                g_system->testNextDeparture(route, t);
            });
            break;
        }

        case ID_BTN_SHORTEST_TIME:
        {
            if(!ensureData()) break;
            string src = allLower(GetEditText(g_hSourceEdit));
            string dest = allLower(GetEditText(g_hDestEdit));
            if(src.empty() || dest.empty())
            {
                MessageBoxA(hwnd, "Enter source and destination stops.", "Input Needed", MB_OK | MB_ICONINFORMATION);
                break;
            }
            RunWithCapturedOutput([src, dest]() {
                g_system->testShortestTime(src, dest);
            });
            break;
        }

        case ID_BTN_CHEAPEST_COST:
        {
            if(!ensureData()) break;
            string src = allLower(GetEditText(g_hSourceEdit));
            string dest = allLower(GetEditText(g_hDestEdit));
            if(src.empty() || dest.empty())
            {
                MessageBoxA(hwnd, "Enter source and destination stops.", "Input Needed", MB_OK | MB_ICONINFORMATION);
                break;
            }
            RunWithCapturedOutput([src, dest]() {
                g_system->testCheapestCost(src, dest);
            });
            break;
        }

        default:
            break;
        }
        break;
    }

    case WM_CTLCOLORSTATIC:
    {
        HDC hdc   = (HDC)wParam;
        HWND hCtrl = (HWND)lParam;

        if (hCtrl == g_hOutput)
        {
            SetBkMode(hdc, OPAQUE);
            SetBkColor(hdc, g_outputBgColor);
            SetTextColor(hdc, RGB(20, 20, 20));
            return (LRESULT)g_hOutputBg;
        }

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(40, 40, 40));
        SetBkColor(hdc, g_mainBgColor);
        return (LRESULT)g_hBgBrush;
    }

    case WM_CTLCOLOREDIT:
    {
        HDC hdc = (HDC)wParam;
        HWND hCtrl = (HWND)lParam;

        if(hCtrl == g_hOutput)
        {
            SetBkColor(hdc, g_outputBgColor);
            SetTextColor(hdc, RGB(20, 20, 20));
            return (LRESULT)g_hOutputBg;
        }

        SetBkColor(hdc, RGB(255, 255, 255));
        SetTextColor(hdc, RGB(20, 20, 20));
        return (LRESULT)GetStockObject(WHITE_BRUSH);
    }

    case WM_CTLCOLORBTN:
    {
        HDC hdc = (HDC)wParam;
        SetBkMode(hdc, TRANSPARENT);
        return (LRESULT)g_hBgBrush;
    }

    case WM_SIZE:
    {
        if (g_hOutput)
        {
            RECT rc;
            GetClientRect(hwnd, &rc);
            int clientW = rc.right - rc.left;
            int clientH = rc.bottom - rc.top;

            int outX = UI_MARGIN;
            int outY = OUTPUT_TOPY;
            int outW = clientW - 2 * UI_MARGIN;
            int outH = clientH - OUTPUT_TOPY - UI_MARGIN;
            if (outH < 50) outH = 50;

            MoveWindow(g_hOutput, outX, outY, outW, outH, TRUE);
        }
        break;
    }

    case WM_DESTROY:
        if(g_hMonoFont) { DeleteObject(g_hMonoFont); g_hMonoFont = NULL; }
        if(g_hBgBrush)  { DeleteObject(g_hBgBrush);  g_hBgBrush  = NULL; }
        if(g_hOutputBg) { DeleteObject(g_hOutputBg); g_hOutputBg = NULL; }
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
