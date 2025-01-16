# CLI에서 Visual Studio 프로젝트 및 솔루션 생성 방법

이 문서는 CLI에서 Visual Studio 프로젝트 및 솔루션을 생성하는 방법에 대한 문서입니다.

## 사전 준비
- Visual Studio 2022 설치

## Visual Studio 프로젝트 생성

CLI에서 다음 명령어를 입력하면 Visual Studio 프로젝트를 생성할 수 있습니다.

> 프로젝트 종류는 console 앱을 기준으로 합니다.

```PowerShell
> dotnet new console --name <OUTPUT_NAME>
```

현재 프로젝트의 이름은 `FlappyBird` 이므로, `<OUTPUT_NAME>`을 `FlappyBird`로 설정하여 아래의 명령어를 입력하여 프로젝트를 생성합니다.

```PowerShell
> dotnet new console --name FlappyBird
```

## Visual Studio 솔루션 생성

CLI에서 다음 명령어를 입력하면 Visual Studio 솔루션을 생성할 수 있습니다.

```PowerShell
> dotnet new sln --name <SOLUTION_NAME>
```

현재 프로젝트의 이름은 `FlappyBird` 이므로, 프로젝트 생성 때와 동일하게 `<SOLUTION_NAME>`을 `FlappyBird`로 설정하여 아래의 명령어를 입력하여 솔루션을 생성합니다.

```PowerShell
> dotnet new sln --name FlappyBird
```

## Visual Studio 솔루션에 프로젝트 추가

솔루션에서 프로젝트를 인식할 수 있도록 추가하는 작업이 필요합니다. 이를 위해 CLI에서 다음 명령어를 입력하면 Visual Studio 솔루션에 프로젝트를 추가할 수 있습니다.

```PowerShell
> dotnet sln add <PROJECT_NAME>
```

생성한 프로젝트으이 이름이 `FlappyBird`이므로, 아래의 명령어를 입력하여 Visual Studio 솔루션에 프로젝트를 추가해줍니다.

```PowerShell
> dotnet sln add FlappyBird.csproj
```

## 참조
- [MSDN: dotnet new <템플릿>](https://learn.microsoft.com/ko-kr/dotnet/core/tools/dotnet-new)
- [MSDN: dotnet sln](https://learn.microsoft.com/ko-kr/dotnet/core/tools/dotnet-sln)