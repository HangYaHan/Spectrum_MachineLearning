设计一个读取光谱数据的 C++ 程序时，考虑到数据分散在有序的若干文件夹中，并且需要具备良好的扩展性和低耦合性，你可以采用以下设计框架和建议：

---

### **设计框架**

#### **1. 数据结构设计**
首先，定义一个通用的数据结构来表示光谱数据。这个数据结构可以是类或结构体，具体取决于你的需求。

- **光谱数据类**：`SpectrumData`
  - 成员变量：
    - `std::vector<double> wavelengths`：波长数据。
    - `std::vector<double> intensities`：强度数据。
    - `std::string filename`：数据文件的名称。
    - `std::string filepath`：数据文件的路径。
  - 方法：
    - `void load(const std::string& filepath)`：加载数据文件。
    - `void print()`：打印光谱数据（调试用）。

#### **2. 文件系统管理**
设计一个类来管理文件夹和文件的遍历。

- **文件系统管理类**：`FileSystemManager`
  - 成员变量：
    - `std::string root_directory`：根目录路径。
  - 方法：
    - `std::vector<std::string> listFiles(const std::string& directory)`：列出指定目录下的所有文件路径。
    - `std::vector<std::string> listDirectories(const std::string& directory)`：列出指定目录下的所有子目录路径。

#### **3. 数据加载器**
设计一个类来负责从文件中加载光谱数据。

- **光谱数据加载器类**：`SpectrumLoader`
  - 成员变量：
    - `FileSystemManager file_manager`：文件系统管理对象。
  - 方法：
    - `std::vector<SpectrumData> loadSpectra(const std::string& root_directory)`：从根目录开始，递归加载所有光谱数据。

#### **4. 业务逻辑处理**
设计一个抽象基类或接口，用于定义对光谱数据的操作。这样可以方便地扩展不同的业务逻辑。

- **抽象处理器基类**：`SpectrumProcessor`
  - 纯虚函数：
    - `void process(const std::vector<SpectrumData>& spectra)`：处理光谱数据。

- **具体处理器类**（示例）：
  - `SpectrumFilter`：对光谱数据进行滤波。
  - `SpectrumAnalyzer`：对光谱数据进行分析。
  - `SpectrumVisualizer`：对光谱数据进行可视化。

#### **5. 主程序**
将各模块组合起来，形成主程序。

- **主程序结构**：
  - 初始化 `FileSystemManager`。
  - 使用 `SpectrumLoader` 加载光谱数据。
  - 创建具体的 `SpectrumProcessor` 实例。
  - 调用 `SpectrumProcessor::process()` 处理数据。

---

### **设计建议**

#### **1. 模块化设计**
- **低耦合**：每个模块（如 `FileSystemManager`、`SpectrumLoader`、`SpectrumProcessor`）之间通过接口或简单的数据结构交互，尽量避免直接依赖。
- **单一职责**：每个类只负责一个功能，例如文件管理、数据加载、数据处理。

#### **2. 工厂模式**
- 使用工厂模式来创建 `SpectrumProcessor` 的实例。这样可以轻松扩展新的处理器类，而不需要修改现有代码。

#### **3. 文件格式抽象**
- 如果你的光谱数据文件格式多种多样（如 CSV、JSON、TXT 等），可以设计一个接口 `FileParser`，然后为每种文件格式实现一个具体的解析器。

#### **4. 配置管理**
- 使用配置文件（如 JSON 或 INI 文件）来管理程序的参数（如根目录路径、文件格式等），而不是硬编码。

#### **5. 异常处理**
- 在文件读取、数据解析等关键步骤中加入异常处理，以提高程序的健壮性。

#### **6. 扩展性设计**
- **开放-封闭原则**：设计时尽量遵循开放-封闭原则，即对扩展开放，对修改封闭。例如，添加新的处理器类时，不需要修改现有代码。
- **插件化**：如果业务逻辑非常复杂，可以考虑将处理器类设计为插件，通过动态加载的方式扩展功能。

#### **7. 数据缓存**
- 如果数据量较大，可以考虑将加载的光谱数据缓存到内存中，以提高处理效率。

---

### **类关系图**

```
+---------------+
| SpectrumData  |
+---------------+
       ^
       |
       |
+---------------+       +-------------------+
| SpectrumLoader|<------| FileSystemManager  |
+---------------+       +-------------------+
       ^
       |
       |
+---------------+
| SpectrumProcessor |
+---------------+
       ^
       |
+-------+---------+
| SpectrumFilter |
+-------+---------+
| SpectrumAnalyzer |
+-------+---------+
| SpectrumVisualizer |
+---------------+
```

---

### **总结**
通过以上设计框架和建议，你可以构建一个模块化、低耦合、易于扩展的光谱数据处理程序。关键点在于将文件管理、数据加载、数据处理等功能分离，并使用接口或抽象类实现业务逻辑的扩展。