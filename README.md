# High Performance C++ Web Server from Scratch

## Benchmark

Using `wrk`:

For 1000 connections, an average 125 microseconds of latency.

```
[sci@dell (C++):~/cpp-webserver]$ wrk -c1000 -d1s http://localhost:8080/
Running 1s test @ http://localhost:8080/
  2 threads and 1000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   125.84us   49.19us   2.08ms   80.77%
    Req/Sec    15.65k    10.35k   28.32k    60.00%
  31103 requests in 1.04s, 2.88MB read
Requests/sec:  29967.24
Transfer/sec:      2.77MB

[sci@dell (C++):~/cpp-webserver]$ 
```
