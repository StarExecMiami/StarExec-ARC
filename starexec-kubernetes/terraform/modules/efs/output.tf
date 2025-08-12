output "efs_file_system_id" {
  description = "ID of the EFS file system"
  value       = aws_efs_file_system.starexec.id
}

output "voldb_access_point_id" {
  description = "ID of the voldb access point"
  value       = aws_efs_access_point.voldb.id
}

output "volstar_access_point_id" {
  description = "ID of the volstar access point"
  value       = aws_efs_access_point.volstar.id
}

output "volpro_access_point_id" {
  description = "ID of the volpro access point"
  value       = aws_efs_access_point.volpro.id
}