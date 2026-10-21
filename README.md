# initcall

> [!CAUTION]
> 本仓库初版代码收集自公开网络，保留作者原始署名，部分迭代内容由本人完成，仅作保存/研究用途，使用风险自担；如有侵权可联系我处理。

提取RT-Thread的initcall框架

- 链接脚本
    ```ld
    SECTIONS
    {
    . = ALIGN(4);
    .init_fn :
      {
        KEEP(*(SORT(.init_fn*)))
      } > FLASH
    }
    ```

## LOG

- [古远以前]：代码裁剪、整理