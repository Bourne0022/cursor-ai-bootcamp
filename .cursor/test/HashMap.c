V put(HashMap* map, K key, V value) {
    // 1. 【索引定位】
    // 请问：如何通过 hash 函数和 map->size 计算出数组下标 index？
    // 注意：需要处理 size_t 到 int 的转换警告。
     int index = hash(key, map->size, map->hashseed) % map->size;

    // 2. 【冲突检查】
    // 逻辑：遍历 map->table[index] 指向的链表。
    // 如果发现 current->key 和传入的 key 相同（用什么函数比较？）：
    //    a. 暂存旧的 value。
    //    b. 给新的 value 做一次 ___深 拷贝（填“深”或“浅”）。
    //    c. 返回旧的 value。
    
    // 3. 【申请与初始化】
    // 逻辑：如果 key 不存在，创建一个新节点 newNode。
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;

    // 为了消除 VS 的 C6001 警告，这里应该立即做一件什么事？
    ____________________________________________________________;

    // 4. 【深拷贝关键行】
    // 请写出给 newNode->key 赋值的那一行代码（使用我们自定义的函数）：


    newNode->value = safe_strdup(value);

    // 5. 【安全防线】
    // 请写出：如果 key 或 value 分配内存失败，该如何安全撤销（释放）？
    if ( !newNode->key || !newNode->value ) {
        
        return NULL;
    }
    free(newNode->value);

    // 6. 【挂载逻辑】
    // 请用两行代码实现“头插法”，将 newNode 挂载到数组的 index 位置：
    map->table[index] = newNode;
    newNode->next = map->table[index];
    map->size++;
    
    return NULL;
}