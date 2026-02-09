# MFCFrame
## MFC的类层次结构体

![](https://i-blog.csdnimg.cn/direct/ea3b330da85d4ea5bb849636f7397987.png)

## 框架的优点

1.   获取所有类列表
2.   获取对象大小
3.   获取类的唯一标号schema；
4.   可以获知继承层级图

# MFCFrame框架优化(2026-02-09)

​	消息映射和命令传递做了框架优化。**在第一次 dispatch 时，把消息表“编译”成哈希索引表（unordered_map）**
 之后查找从 O(N) 变成 **O(1)**，而且**不破坏现有的宏和用法**。

## 提交记录

​	**保留 master 不变的前提下**(第一版本保留)，提交新框架到新分支，并打一个 **Tag 版本号**（比如 v2.0）来标记这个版本

1.   创建新分支MFCFrame_V2，并且会自动切换到新分支上去

```bash
git checkout -b MFCFrame_V2
```

2.   添加修改到暂存区

```bas
git add .
```

3.   提交修改

```bash
git commit -m "Add new message dispatch framework v2 with examples"
```

4.   打 Tag 标记版本

```bash
git tag -a v2.0 -m "Message dispatch framework v2 release"
```

>   `-a v2.0` 表示 Tag 名称为 v2.0
>
>   `-m` 是说明信息

5.   推送分支到远程仓库

```bash
git push origin MFCFrame_V2
```

>   GitHub 上会出现 `MFCFrame_V2` 分支。

6.   推送 Tag 到远程

```bash
git push origin v2.0
```

>   这样远程仓库就会保存 v2.0 标签。

7.   回到 master 分支

```bash
git checkout master
```

>   master 保留原来的旧版本，干净无修改。
