# TextPulse

开发中的开源视觉小说引擎。
鸽了,顺便让codex拉了几坨代码在这充数

当前仓库已提供最小可运行原型：
- `textpulse_runtime`：基于 **OpenGL + GLFW** 的运行时窗口循环，并初始化 **OpenAL** 音频设备。
- `textpulse_editor`：独立的创作编辑器程序（独立可执行文件），同样使用 GLFW/OpenGL 和 OpenAL 初始化。

## 构建

```bash
cmake -S . -B build
cmake --build build
```

## 运行

```bash
./build/textpulse_runtime
./build/textpulse_editor
```
