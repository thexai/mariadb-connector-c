static inline wchar_t* to_utf16(const char* str)
{
  if (str == NULL)
    return NULL;

  size_t length = strlen(str);

  int result = MultiByteToWideChar(CP_UTF8, 0, str, (int)length, NULL, 0);
  if (result == 0)
    return NULL;

  length = (size_t)result + 1;
  wchar_t* strW = (wchar_t*)malloc(length * sizeof(wchar_t));
  if (strW == NULL)
    return NULL;

  result = MultiByteToWideChar(CP_UTF8, 0, str, result, strW, (int)length);

  if (result == 0)
  {
    free(strW);
    return NULL;
  }

  if (strW[length - 1] != L'\0')
    strW[length - 1] = L'\0';

  return strW;
}

static inline char* to_utf8(const wchar_t* str)
{
    if (str == NULL)
        return NULL;

    size_t length = wcslen(str);

    int result = WideCharToMultiByte(CP_UTF8, 0, str, (int)length, NULL, 0, NULL, NULL);
    if (result == 0)
        return NULL;

    int required = result + 1;
    char* newStr = (char*)malloc(required);
    if (newStr == NULL)
        return NULL;

    result = WideCharToMultiByte(CP_UTF8, 0, str, (int)length, newStr, required, NULL, NULL);
    if (result == 0)
    {
        free(newStr);
        return NULL;
    }

    if (newStr[required - 1] != '\0')
        newStr[required - 1] = '\0';

    return newStr;
}

static inline HANDLE uwp_create_file(
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile
)
{
    if (dwShareMode == 0)
        dwShareMode = FILE_SHARE_READ;

    const DWORD flagsMask = 0xFFFF0000;

    CREATEFILE2_EXTENDED_PARAMETERS ext;
    ZeroMemory(&ext, sizeof(CREATEFILE2_EXTENDED_PARAMETERS));
    ext.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
    ext.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
    ext.dwFileFlags = dwFlagsAndAttributes & flagsMask;

    return CreateFile2(lpFileName, dwDesiredAccess, dwShareMode, dwCreationDisposition, &ext);
}
