#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype> // for isalnum

std::string urlEncode(const std::string &s)
{
    std::ostringstream out;
    for (unsigned char c : s)
    {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
            out << c;
        else
            out << '%' << std::uppercase << std::hex << std::setw(2)
                << std::setfill('0') << int(c);
    }
    return out.str();
}

struct Edge
{
    int first, second;
};

struct Vertex
{
    std::vector<int> adjacentVertex;
};

// ---------------- DFS ----------------

bool main_dfs(std::vector<Vertex> &vertices, std::vector<bool> &seen, int start)
{
    std::cout << start + 1 << " ";
    seen[start] = true;
    for (int i = 0; i < (int)vertices[start].adjacentVertex.size(); i++)
    {
        int v = vertices[start].adjacentVertex[i];
        if (!seen[v])
        {
            main_dfs(vertices, seen, v);
        }
    }
    return true;
}

bool dfs(std::vector<Vertex> &vertices, int nV)
{
    int start = 0;
    std::cout << "Enter start: ";
    std::cin >> start;
    std::cout << "DFS: \n  ";
    std::vector<bool> seen{};
    for (int i = 0; i < nV; i++)
    {
        seen.push_back(false);
    }
    main_dfs(vertices, seen, start);
    return true;
}

// ---------------- BFS ----------------

bool main_bfs(std::vector<Vertex> &vertices, std::vector<bool> &seen, int start)
{
    std::cout << start + 1 << " ";
    seen[start] = true;

    for (int i = 0; i < (int)vertices[start].adjacentVertex.size(); i++)
    {
        if (!seen[vertices[start].adjacentVertex[i]])
        {
            std::cout << vertices[start].adjacentVertex[i] + 1 << " ";
            seen[vertices[start].adjacentVertex[i]];
        }
    }

    for (int i = 0; i < (int)vertices[start].adjacentVertex.size(); i++)
    {
        if (!seen[vertices[start].adjacentVertex[i]])
        {
            main_bfs(vertices, seen, vertices[start].adjacentVertex[i]);
        }
    }
    return true;
}

bool bfs(std::vector<Vertex> &vertices, int nV)
{
    int start = 0;
    std::cout << "Enter start: ";
    std::cin >> start;
    std::cout << "DFS: \n  ";
    std::vector<bool> seen{};
    for (int i = 0; i < nV; i++)
    {
        seen.push_back(false);
    }
    main_bfs(vertices, seen, start - 1);
    return true;
}

// ---------------- INPUT ----------------

bool inp(int &nV, int &nE)
{
    std::cout << "Enter count of vertices: ";
    std::cin >> nV;

    std::cout << "Enter count of edges: ";
    std::cin >> nE;

    return true;
}

//  ***************  اینجا فقط همین را اصلاح کردم  ***************
//      از pass-by-value → pass-by-reference  
//  ***************************************************************
bool inputEdge(std::vector<Vertex> &vertices, std::vector<Edge> &edges, int nV, int nE)
{
    std::cout << "Enter edges (u v):" << std::endl;

    for (int i = 0; i < nE; i++)
    {
        int u, v;
        std::cin >> u >> v;

        u -= 1;
        v -= 1;

        if (u < 0 || u >= nV || v < 0 || v >= nV)
        {
            std::cout << "Invalid edge index: (" << u << ", " << v << ")" << std::endl;
            --i;
            continue;
        }

        edges.push_back({u, v});
        vertices[u].adjacentVertex.push_back(v);
        vertices[v].adjacentVertex.push_back(u);
    }

    for (auto &v : vertices)
        sort(v.adjacentVertex.begin(), v.adjacentVertex.end());

    return true;
}

// ---------------- MAIN ----------------

int main()
{
    using namespace std;

    int nE = 0;
    int nV = 0;
    inp(nV, nE);

    vector<Vertex> vertices(nV);
    vector<Edge> edges;
    edges.reserve(nE);

    inputEdge(vertices, edges, nV, nE);

    dfs(vertices, nV);
    cout << endl;

    bfs(vertices, nV);
    cout << endl;

    // --- ساخت رشته DOT ---
    std::ostringstream ss;
    ss << "graph G {\n";
    for (auto &e : edges)
    {
        ss << "    " << e.first + 1 << " -- " << e.second + 1 << ";\n";
    }
    ss << "}";
    std::string dotText = ss.str();

    // ذخیره
    {
        std::ofstream out("graph.dot");
        out << dotText << "\n";
    }

    // لینک آنلاین
    std::string encoded = urlEncode(dotText);
    std::string url =
        "https://dreampuf.github.io/GraphvizOnline/#" + encoded;

    cout << "\nDOT file generated: graph.dot\n";
    cout << "\nOpen graph online:\n"
         << url << "\n";

    int ok;
    cin >> ok;

    return 0;
}
