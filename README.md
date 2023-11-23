......

camera其实挺简单的，但是记得角度和弧度的转换，不然看着很怪但就是不知道哪里有问题...

很显然， lightshader和objectshader之间是不能相互通信的，在lightvertex,lightfragcolor的(out vecX ...)自然也不能被object接收到，目前是靠新建uniform和同时向两者传递相同的信息解决的
11/22/23

多加了点参数，感觉光照效果确实更好了，以及建了俩struct来管理确实方便多了
