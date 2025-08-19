output "efs_file_system_id" {
  description = "ID of the EFS file system"
  value       = aws_efs_file_system.starexec.id
}

output "shared_access_point_id" {
  description = "ID of the shared access point"
  value       = aws_efs_access_point.starexec_shared.id
}