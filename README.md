# High Performance C++ Web Server from Scratch

## Benchmark

Using `wrk`:

FastAPI:

```
[sci@dell (C++):~/cpp-webserver]$ wrk -t 32 -c1000 -d1s http://localhost:8000
Running 1s test @ http://localhost:8000
  32 threads and 1000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   333.11ms   68.02ms 488.83ms   73.39%
    Req/Sec    99.75     67.20   300.00     75.20%
  2589 requests in 1.10s, 359.27KB read
Requests/sec:   2353.66
Transfer/sec:    326.61KB
```

Single thread C++ web server:
```

[sci@dell (C++):~/cpp-webserver]$ wrk -t 32 -c1000 -d1s http://localhost:8080
Running 1s test @ http://localhost:8080
  32 threads and 1000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     8.40ms   67.26ms 942.53ms   98.00%
    Req/Sec     1.32k     2.62k   17.06k    91.89%
  18258 requests in 1.10s, 1.69MB read
Requests/sec:  16590.90
Transfer/sec:      1.53MB

[sci@dell (C++):~/cpp-webserver]$ 
```
