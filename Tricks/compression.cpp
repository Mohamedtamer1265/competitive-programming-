sort(begin(comp), end(comp));
comp.resize(unique(begin(comp), end(comp)) - begin(comp));
auto idx = [&](int x) -> int {
    return lower_bound(begin(comp), end(comp), x) - begin(comp);
};
ll maxelement = 0;
for(ll i = 0;i<n;i++)
{
   ele[i] = idx(ele[i]);
   maxelement = max(maxelement,ele[i]);
}