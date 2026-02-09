#include "cMFCMsgAndCmd.h"

// ==================== 自定义消息参数结构 ====================
// 温度数据结构：用于传递温度读数和校准系数
struct TemperatureData {
    int value;         // 温度值（例如 25°C）
    float calibration; // 校准因子（例如 0.98）
};

// 湿度数据结构：用于传递湿度读数和校准系数
struct HumidityData {
    int value;        // 湿度值（例如 60%）
    float calibration; // 校准因子（例如 1.05）
};

// ==================== 基类传感器：所有传感器的公共基类 ====================
class CSensorBase : public CCmdTarget {
    // 声明消息映射（宏展开后生成 getMessageMap 和 getThisMessageMap）
DECLARE_MESSAGE_MAP()

public:
    // 处理初始化命令（ID=1），无参数
    void onInit(void* param) {
        std::cout << "[CSensorBase] 初始化传感器" << std::endl;
    }
};

// 定义 CSensorBase 的消息映射表：
// - 继承自 CCmdTarget
// - 将命令 ID=1 映射到 onInit 成员函数
BEGIN_MESSAGE_MAP(CSensorBase, CCmdTarget)
    ON_COMMAND(1, &CSensorBase::onInit)  // 注意：宏内部自动取 &ThisClass::onInit，此处可省略 &
END_MESSAGE_MAP()


// ==================== 温度传感器：派生自 CSensorBase ====================
class CTemperatureSensor : public CSensorBase {
DECLARE_MESSAGE_MAP()

public:
    // 处理温度读取命令（ID=101），接收 TemperatureData* 类型参数
    void onReadTemperature(void* param) {
        if (param) {
            // 安全转换为具体参数类型（实际应由 dispatchMessage 保证类型匹配）
            TemperatureData* data = static_cast<TemperatureData*>(param);
            std::cout << "[CTemperatureSensor] 温度值: " << data->value
                      << ", 校准: " << data->calibration << std::endl;
        } else {
            std::cout << "[CTemperatureSensor] 未传入温度数据" << std::endl;
        }
    }
};

// 温度传感器的消息映射：
// - 继承自 CSensorBase（会继承 ID=1 的 onInit）
// - 新增 ID=101 -> onReadTemperature
BEGIN_MESSAGE_MAP(CTemperatureSensor, CSensorBase)
    ON_COMMAND(101, &CTemperatureSensor::onReadTemperature)
END_MESSAGE_MAP()


// ==================== 湿度传感器：派生自 CSensorBase ====================
class CHumiditySensor : public CSensorBase {
DECLARE_MESSAGE_MAP()

public:
    // 处理湿度读取命令（ID=102），接收 HumidityData* 类型参数
    void onReadHumidity(void* param) {
        if (param) {
            HumidityData* data = static_cast<HumidityData*>(param);
            std::cout << "[CHumiditySensor] 湿度值: " << data->value
                      << ", 校准: " << data->calibration << std::endl;
        } else {
            std::cout << "[CHumiditySensor] 未传入湿度数据" << std::endl;
        }
    }
};

// 湿度传感器的消息映射：
// - 继承自 CSensorBase
// - 新增 ID=102 -> onReadHumidity
BEGIN_MESSAGE_MAP(CHumiditySensor, CSensorBase)
    ON_COMMAND(102, &CHumiditySensor::onReadHumidity)
END_MESSAGE_MAP()


// ==================== 控制器：协调多个传感器 ====================
class CController : public CCmdTarget {
DECLARE_MESSAGE_MAP()

public:
    // 控制器内部持有两个传感器实例（组合关系）
    CTemperatureSensor tempSensor;
    CHumiditySensor humSensor;

    // 处理“检查所有传感器”命令（ID=201）
    void onCheckSensors(void* param) {
        std::cout << "[CController] 检查所有传感器" << std::endl;

        // 创建模拟数据
        TemperatureData tdata{25, 0.98f};
        HumidityData hdata{60, 1.05f};

        // 直接调用子对象的消息派发接口（体现消息系统解耦能力）
        tempSensor.dispatchMessage(MSG_COMMAND, 101, &tdata);
        humSensor.dispatchMessage(MSG_COMMAND, 102, &hdata);
    }

    // 处理窗口/对象销毁事件（MSG_DESTROY）
    void onDestroy(void* param) {
        std::cout << "void onDestroy(void* param)" << std::endl;
    }
};

// 控制器的消息映射：
// - 继承自 CCmdTarget
// - ID=201 -> onCheckSensors
// - MSG_DESTROY -> onDestroy
BEGIN_MESSAGE_MAP(CController, CCmdTarget)
    ON_COMMAND(201, &CController::onCheckSensors)
    ON_DESTROY(&CController::onDestroy)
END_MESSAGE_MAP()


// ==================== 主函数：演示消息派发流程 ====================
int main() {
    // 创建控制器实例（会自动构造其内部的传感器对象）
    CController controller;

    // ------------------ 步骤1：分别初始化两个传感器 ------------------
    std::cout << ">>> 初始化传感器 <<<" << std::endl;
    controller.tempSensor.dispatchMessage(MSG_COMMAND, 1);  // 调用 CSensorBase::onInit
    controller.humSensor.dispatchMessage(MSG_COMMAND, 1);

    // ------------------ 步骤2：直接读取传感器数据 ------------------
    std::cout << "\n>>> 直接读取传感器数据 <<<" << std::endl;
    TemperatureData tdata{25, 0.98f};
    HumidityData hdata{60, 1.05f};

    controller.tempSensor.dispatchMessage(MSG_COMMAND, 101, &tdata);
    controller.humSensor.dispatchMessage(MSG_COMMAND, 102, &hdata);

    // ------------------ 步骤3：通过控制器统一检查 ------------------
    std::cout << "\n>>> 通过控制器统一检查 <<<" << std::endl;
    controller.dispatchMessage(MSG_COMMAND, 201);  // 触发 onCheckSensors

    // ------------------ 步骤4：触发销毁事件 ------------------
    std::cout << "\n>>> 触发销毁事件 <<<" << std::endl;
    controller.dispatchMessage(MSG_DESTROY, 0);  // ID 对 MSG_DESTROY 无效，设为 0

    return 0;
}