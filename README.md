# Http-copy
This is tool for copy http request to other http server, base on log

# NOTICE
You can use nginx 1.13.4 ngx_http_mirror_module later!

# Feature
* use simple and safe for master 
* support nginx and support other http server by config

# How to use
* git clone https://github.com/hongliuliao/http-copy
* cd http-copy && make
* cd output && config conf/copy.conf
* nohup ./bin/http_copy &
* curl http://master_server/hello
* see slave server logs

# How to config
* log_reg=.* "GET (.*) HTTP.* ==> log_reg for nginx, the reg in () is url
* log_path=/home/liao/programs/nginx/logs/access.log ==> the log_path to watch
* dist_host=localhost:8081 ==> slave server
