Basic FastAPI web application as a point of comparison for benchmarking.

## Benchmark

With `wrk`:

307 milliseconds average latency per request.

```
[sci@dell (C++):~/cpp-webserver]$ wrk -c1000 -d1s http://localhost:8000
Running 1s test @ http://localhost:8000
  2 threads and 1000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   307.28ms   61.89ms 437.51ms   69.10%
    Req/Sec     1.36k   444.09     1.94k    66.67%
  2560 requests in 1.05s, 355.24KB read
Requests/sec:   2441.91
Transfer/sec:    338.86KB

[sci@dell (C++):~/cpp-webserver]$ 
```
