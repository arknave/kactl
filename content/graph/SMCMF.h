/**
 * Author: Stjepan Glavina
 * Date: 2016-10-18
 * License: Unlicense
 * Source: stjepang/snippets
 * Description:  To use, call init(n), then add edges using edge(x, y, c, w), and finally call run(src, sink). Uses DFS, good for shallow graphs
 * Time: $O(V E^3)$
 */
#pragma once
namespace mcmf {
    const int MAXV = 1000100;
    const int MAXE = 1000100;
    const ll oo = 1e18;

    int V, E;
    int last[MAXV], curr[MAXV], bio[MAXV]; ll pi[MAXV];
    int next[MAXE], adj[MAXE]; ll cap[MAXE], cost[MAXE];

    void init(int n) {
        V = n;
        E = 0;
        REP(i, V) last[i] = -1;
    }

    void edge(int x, int y, ll c, ll w) {
        adj[E] = y; cap[E] = c; cost[E] = +w; next[E] = last[x]; last[x] = E++;
        adj[E] = x; cap[E] = 0; cost[E] = -w; next[E] = last[y]; last[y] = E++;
    }

    ll push(int x, int sink, ll flow) {
        if (x == sink) return flow;
        if (bio[x]) return 0;
        bio[x] = true;

        for (int &e = curr[x]; e != -1; e = next[e]) {
            int y = adj[e];

            if (cap[e] && pi[x] == pi[y] + cost[e])
                if (ll f = push(y, sink, min(flow, cap[e])))
                    return cap[e] -= f, cap[e^1] += f, f;
        }
        return 0;
    }

    pair<ll, ll> run(int src, int sink) {
        ll total = 0;
        ll flow = 0;

        REP(i, V) pi[i] = oo;
        pi[sink] = 0;

        for (;;) {
            bool done = true;
            REP(x, V) for (int e = last[x]; e != -1; e = next[e])
                if (cap[e] && pi[x] > pi[adj[e]] + cost[e])
                    pi[x] = pi[adj[e]] + cost[e], done = false;
            if (done) break;
        }

        for (;;) {
            REP(i, V) bio[i] = false;
            REP(i, V) curr[i] = last[i];

            while (ll f = push(src, sink, oo)) {
                total += pi[src] * f;
                flow += f;
                REP(i, V) bio[i] = false;
            }

            ll inc = oo;
            REP(x, V) if (bio[x]) {
                for (int e = last[x]; e != -1; e = next[e]) {
                    int y = adj[e];
                    if (cap[e] && !bio[y]) inc = min(inc, pi[y] + cost[e] - pi[x]);
                }
            }
            if (inc == oo) break;

            REP(i, V) if (bio[i]) pi[i] += inc;
        }
        return {total, flow};
    }
}
