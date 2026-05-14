#include <vrs/os/Time.h>

#define DEFAULT_LOG_CHANNEL "vrs_consumer_test"
#include <vrs/oss/logging/Verify.h>

#include <vrs/DataLayout.h>
#include <vrs/DataPieces.h>
#include <vrs/RecordFileWriter.h>
#include <vrs/RecordFormat.h>
#include <vrs/Recordable.h>

namespace {

class Metadata : public vrs::AutoDataLayout {
 public:
  vrs::DataPieceValue<uint32_t> sensorValue{"my_sensor"};
  vrs::AutoDataLayoutEnd endLayout;
};

class SampleRecordable : public vrs::Recordable {
 public:
  SampleRecordable()
      : vrs::Recordable(
            vrs::RecordableTypeId::SampleDeviceRecordableClass,
            "conda-forge/vrs/consumer-test") {
    addRecordFormat(
        vrs::Record::Type::DATA,
        kDataRecordFormatVersion,
        metadata_.getContentBlock(),
        {&metadata_});
  }

  const vrs::Record* createConfigurationRecord() override {
    return createRecord(vrs::os::getTimestampSec(), vrs::Record::Type::CONFIGURATION, 0);
  }

  const vrs::Record* createStateRecord() override {
    return createRecord(vrs::os::getTimestampSec(), vrs::Record::Type::STATE, 0);
  }

  void createDataRecord(uint32_t sensorValue) {
    metadata_.sensorValue.set(sensorValue);
    createRecord(
        vrs::os::getTimestampSec(),
        vrs::Record::Type::DATA,
        kDataRecordFormatVersion,
        vrs::DataSource(metadata_));
  }

 private:
  static constexpr uint32_t kDataRecordFormatVersion = 1;
  Metadata metadata_;
};

} // namespace

int main() {
  vrs::RecordFileWriter writer;
  SampleRecordable recordable;
  writer.addRecordable(&recordable);

  for (uint32_t value = 0; value < 8; ++value) {
    recordable.createDataRecord(value);
  }

  XR_VERIFY(writer.writeToFile("my_record_file.vrs") == 0);
  return 0;
}
