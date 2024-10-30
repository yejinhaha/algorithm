import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

# 작업의 시작 시간과 종료 시간을 정의
tasks = {
    't1': (7, 8),
    't2': (3, 7),
    't3': (1, 5),
    't4': (5, 9),
    't5': (0, 2),
    't6': (6, 8),
    't7': (1, 6)
}

# 작업을 시작 시간 기준으로 정렬
sorted_tasks = sorted(tasks.items(), key=lambda x: x[1][0])

# Job Scheduling 알고리즘 (Earliest Start Time First)
machine_schedules = [[]]  # 첫 번째 기계 초기화

for task_name, (start, end) in sorted_tasks:
    assigned = False
    # 현재 작업을 할당할 수 있는 기계를 찾음
    for machine in machine_schedules:
        if not machine or machine[-1][2] <= start:  # 마지막 작업의 종료 시간 <= 현재 작업의 시작 시간
            machine.append((task_name, start, end))
            assigned = True
            break
    
    # 할당할 수 있는 기계가 없으면 새 기계를 추가
    if not assigned:
        machine_schedules.append([(task_name, start, end)])

# 각 작업에 색상을 할당 (범례와 동일한 색상 사용)
color_palette = plt.cm.Paired.colors
colors = {f't{i+1}': color_palette[i] for i in range(len(tasks))}

# 시각화
fig, ax = plt.subplots(figsize=(10, 3))

# 각 기계별로 작업을 그리기
for machine_idx, machine in enumerate(machine_schedules):
    for task_name, start, end in machine:
        ax.add_patch(mpatches.Rectangle((start, machine_idx), end - start, 0.8, color=colors[task_name], label=task_name))
        ax.text((start + end) / 2, machine_idx + 0.4, task_name, ha='center', va='center', color='black')

# 축과 레이블 설정
ax.set_ylim(-0.5, len(machine_schedules) - 0.5)
ax.set_xlim(0, 9)
ax.set_yticks(range(len(machine_schedules)))
ax.set_yticklabels([f'Machine {i + 1}' for i in range(len(machine_schedules))])
ax.set_xlabel("Time")
ax.set_title("Job Scheduling (Earliest Start Time First)")

# 범례 추가
handles = [mpatches.Patch(color=colors[f't{i+1}'], label=f't{i+1}') for i in range(len(tasks))]
plt.legend(handles=handles, loc='upper right', bbox_to_anchor=(1.15, 1))

plt.grid(axis='x')
plt.show()
