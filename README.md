......

camera其实挺简单的，但是记得角度和弧度的转换，不然看着很怪但就是不知道哪里有问题...

很显然， lightshader和objectshader之间是不能相互通信的，在lightvertex,lightfragcolor的(out vecX ...)自然也不能被object接收到，目前是靠新建uniform和同时向两者传递相同的信息解决的
11/22/23

多加了点参数，感觉光照效果确实更好了，以及建了俩struct来管理确实方便多了

文件交错位置想删了再交，或者干脆把本地最新的全传过去，但是push不知道为什么一直有问题。。。
git rm ... 也一直不起作用，最后靠githubDesktop解决了，clone一份到本地然后(还非要)打开本地文件夹删文件再push(为什么这时候push又起作用了)。。。
