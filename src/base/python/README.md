# python相关的基础库

## 目录的整体介绍

    - file_util : 文件处理相关的基础接口
      - key_value_file_reader: 读取key-value形式的文件到dict中
      - sequential_encoder: 读取文件的第1列，并顺序编码
    - path_util : 路径相关的基础接口
      - project_path_getter: 项目相关路径的基础接口
    - text_util : 文本处理相关的基础接口
      - base_text_util: （中文）文本处理的基础接口
      - character_segment: （中文）字粒度切分的基础接口
      - pattern_match_util: 正则表达式匹配的基础接口
    - util : 其他基础接口
      - datetime_util: 日期时间处理的基础接口
      - log_util: 日志处理的基础接口
