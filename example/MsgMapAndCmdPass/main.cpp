#include "cMFCMsgAndCmd.h"

struct TemperatureData {
    int value;
    float calibration;
};

struct HumidityData {
    int value;
    float calibration;
};

// ------------------ 基类传感器 ------------------
class CSensorBase : public CCmdTarget {
DECLARE_MESSAGE_MAP()
public:
    void onInit(void* param) {
        std::cout << "[CSensorBase] 初始化传感器" << std::endl;
    }
};

BEGIN_MESSAGE_MAP(CSensorBase, CCmdTarget)
    ON_COMMAND(1, &CSensorBase::onInit)
END_MESSAGE_MAP()

// ------------------ 温度传感器 ------------------
class CTemperatureSensor : public CSensorBase {
DECLARE_MESSAGE_MAP()
public:
    void onReadTemperature(void* param) {
        if (param) {
            TemperatureData* data = static_cast<TemperatureData*>(param);
            std::cout << "[CTemperatureSensor] 温度值: " << data->value
                      << ", 校准: " << data->calibration << std::endl;
        } else {
            std::cout << "[CTemperatureSensor] 未传入温度数据" << std::endl;
        }
    }
};

BEGIN_MESSAGE_MAP(CTemperatureSensor, CSensorBase)
                    ON_COMMAND(101, &CTemperatureSensor::onReadTemperature)
END_MESSAGE_MAP()

// ------------------ 湿度传感器 ------------------
class CHumiditySensor : public CSensorBase {
DECLARE_MESSAGE_MAP()
public:
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

BEGIN_MESSAGE_MAP(CHumiditySensor, CSensorBase)
    ON_COMMAND(102, &CHumiditySensor::onReadHumidity)
END_MESSAGE_MAP()

// ------------------ 控制器 ------------------
class CController : public CCmdTarget {
DECLARE_MESSAGE_MAP()
public:
    // 控制器内部持有传感器对象
    CTemperatureSensor tempSensor;
    CHumiditySensor humSensor;

    void onCheckSensors(void* param) {
        std::cout << "[CController] 检查所有传感器" << std::endl;

        // 调用子对象消息
        TemperatureData tdata{25, 0.98f};
        HumidityData hdata{60, 1.05f};

        tempSensor.dispatchMessage(MSG_COMMAND, 101, &tdata);
        humSensor.dispatchMessage(MSG_COMMAND, 102, &hdata);
    }

    void onDestroy(void* param){
        std::cout << "void onDestroy(void* param)" << std::endl;
    }
};

BEGIN_MESSAGE_MAP(CController, CCmdTarget)
    ON_COMMAND(201, &CController::onCheckSensors)
    ON_DESTROY(&CController::onDestroy)
END_MESSAGE_MAP()

int main() {
    CController controller;

    // 初始化传感器
    controller.tempSensor.dispatchMessage(MSG_COMMAND, 1);
    controller.humSensor.dispatchMessage(MSG_COMMAND, 1);

    // 读取温度和湿度
    TemperatureData tdata{25, 0.98f};
    HumidityData hdata{60, 1.05f};

    controller.tempSensor.dispatchMessage(MSG_COMMAND, 101, &tdata);
    controller.humSensor.dispatchMessage(MSG_COMMAND, 102, &hdata);

    // 控制器检查所有传感器
    controller.dispatchMessage(MSG_COMMAND, 201);

    controller.dispatchMessage(MSG_DESTROY, 0);
    return 0;
}
