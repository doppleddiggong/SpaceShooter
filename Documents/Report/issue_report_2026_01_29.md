# QA Issue Report (2026-01-29)

## 요약
- 수정된 이슈 3
- 남은 이슈 2
- 판단 요약 초기화/타이머 설정 누락 등 런타임 상태 초기화 문제를 보완해 해결됨

## 수정 내역

### Issue #1 시작 시 플레이어 HP UI가 0으로 표시됨
- 우선순위 P2
- 수정 내용 HP UI 초기 표시 로직 보완 (세부 변경 내역 미기재)
- 검증 방법 PIE 실행 후 HP UI 정상 표시 확인

### Issue #2 적 발사 패턴이 종료되지 않고 반복 실행되는 문제
- 우선순위 P2
- 수정 내용 CurrentBurstCount 초기화 및 TryStartFiring에서 bHasFired 검사 추가
- 검증 방법 PIE 실행 후 발사 패턴 정상 표시 확인

### Issue #4 적 총알 수명이 적용되지 않아 장시간 잔존
- 우선순위 P3
- 수정 내용 SetActive(true) 시 LifeTime 타이머 시작, OnLifeTimeExpired()에서 Destroy() 호출 추가
- 검증 방법 ActorTracking.log로 BP_EnemyBullet_C 개수 안정화 확인 (12~21 범위 유지)

## 남은 이슈

### Issue #3 SpawnPoint가 없으면 적 스폰 시 크래시 가능
- 관리 대상 사유 상태 Open (해결 내역 없음)

### Issue #5 SpawnFrequency 비정상 설정으로 성능 저하
- 관리 대상 사유 해결 완료일이 2026-01-30로 기준일(2026-01-29) 이후

## 참고 자료
- 관련 로그 파일 ActorTracking.log
- 트레이스 파일 Unreal Insights 트레이스, TimerStats.csv