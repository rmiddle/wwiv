/**************************************************************************/
/*                                                                        */
/*                            WWIV Version 5                              */
/*           Copyright (C)2020-2022, WWIV Software Services               */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/**************************************************************************/
#ifndef INCLUDED_SDK_FILES_FILE_RECORD_H
#define INCLUDED_SDK_FILES_FILE_RECORD_H

#include "fmt/format.h"
#include "sdk/config.h"
#include "sdk/vardec.h"

#include <optional>
#include <string>

namespace wwiv::core {
class DateTime;
}

namespace wwiv::sdk::files {

class FileName final {
public:
  explicit FileName(std::string aligned_filename);
  FileName(const FileName& that);
  ~FileName() = default;

  /** Returns the aligned version of the filename, this is padded and uppercase as 8.3. */
  [[nodiscard]] const std::string& aligned_filename() const noexcept;
  /** Returns the unaligned version of the filename, this is nonpadded and lowercase. */
  [[nodiscard]] const std::string& unaligned_filename() const noexcept;
  /** Returns the basename of the filename, this is not space padded */
  [[nodiscard]] std::string basename() const;
  /** Returns the extension of the filename, this is not space padded */
  [[nodiscard]] std::string extension() const;

  static std::optional<FileName> FromUnaligned(const std::string& unaligned_name);
  friend std::ostream& operator<<(std::ostream& os, const FileName& f);

private:
  const std::string aligned_filename_;
  const std::string unaligned_filename_;
};

class FileRecord final {
public:
  explicit FileRecord(const uploadsrec& u) : u_(u) {}
  FileRecord();
  FileRecord(const FileRecord&);
  FileRecord& operator=(const FileRecord&);
  ~FileRecord() = default;

  [[nodiscard]] uploadsrec& u() { return u_; }
  [[nodiscard]] const uploadsrec& u() const { return u_; }
  [[nodiscard]] uint32_t numbytes() const noexcept;
  void set_numbytes(int size);
  [[nodiscard]] uint16_t ownerusr() const noexcept;
  void set_ownerusr(int o);
  [[nodiscard]] uint16_t ownersys() const noexcept;
  void set_ownersys(int o);
  [[nodiscard]] bool has_extended_description() const noexcept;
  void set_extended_description(bool b);

  [[nodiscard]] bool pd_or_shareware() const noexcept { return mask(mask_PD); }
  void set_pd_or_shareware(bool b) { set_mask(mask_PD, b); }

  [[nodiscard]] bool mask(int mask) const;
  void set_mask(int mask, bool on);

  bool set_filename(const FileName& filename);
  bool set_filename(const std::string& unaligned_filename);
  bool set_description(const std::string& desc);
  [[nodiscard]] std::string description() const;
  bool set_uploaded_by(const std::string& name);
  [[nodiscard]] std::string uploaded_by() const;
  [[nodiscard]] wwiv::core::DateTime date() const;
  [[nodiscard]] std::string actual_date() const;
  bool set_date(const wwiv::core::DateTime& dt);
  bool set_actual_date(const wwiv::core::DateTime& dt);
  [[nodiscard]] FileName filename() const;
  [[nodiscard]] std::string aligned_filename() const;
  [[nodiscard]] std::string unaligned_filename() const;
  friend std::ostream& operator<<(std::ostream& os, const FileRecord& f);

private:
  uploadsrec u_;
};

std::string align(const std::string& file_name);
std::string unalign(const std::string& file_name);

std::filesystem::path FilePath(const std::filesystem::path& directory_name,
                                   const FileRecord& f);

std::filesystem::path FilePath(const std::filesystem::path& directory_name,
                                   const FileName& f);
} // namespace wwiv::sdk::files

template <> struct fmt::formatter<wwiv::sdk::files::FileRecord> : fmt::formatter<string_view> {
  // parse is inherited from formatter<string_view>.
  template <typename FormatContext>
  auto format(wwiv::sdk::files::FileRecord r, FormatContext& ctx) {
    return formatter<string_view>::format(r.unaligned_filename(), ctx);
  }
};

#endif  // INCLUDED_SDK_FILES_FILE_RECORD_H
