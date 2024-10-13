# 对`remove()` 的修改

使 `remove()` 移除 `currentPos` 所指向的节点，并使其指向下一个节点。因为这样看起来更加合理。

当然，如果没有下一个节点，那么 `currentPos` 会返回上一个节点。此时 `remove()` 等同移除末尾元素。

例如在示例程序中 `c2.remove()` 的结果会是
```
1.5 2 9 4.7 8.8 // 原始数据，currentPos 指向9

1.5 2 4.7 8.8 // 移除9，currentPos 指向4.7
1.5 2 8.8 // 移除4.7, currentPos 指向8.8
1.5 2 // 移除8.8, currentPos 指向2
1.5 // 移除2, currentPos 指向1.5
// 移除1.5, 成为空数组
// 没有任何事发生

```
且`currentPos`指向`4.7`。
